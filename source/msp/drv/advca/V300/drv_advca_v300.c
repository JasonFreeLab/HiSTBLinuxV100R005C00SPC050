/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_advca_v300.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_advca_internal.h"
#include "drv_advca_external.h"
#include "asm/io.h"
static HI_U32 *g_pDrvSema = NULL;


static HI_S32 DRV_ADVCA_Ioctl_Child_GET_VENDOR_ID(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    CA_OTP_VENDOR_TYPE_E *penVendorID = (CA_OTP_VENDOR_TYPE_E *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetVendorId(penVendorID);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_KL_DPA_CLK_SEL_EN(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_BOOL bValue = *(HI_BOOL *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetKlDPAClkSelEn(bValue);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_KL_DPA_CLK_SEL_EN(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_BOOL *pbValue = (HI_BOOL *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetKlDPAClkSelEn(pbValue);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_KL_DPA_FILTER_CLK_EN(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_BOOL bValue = *(HI_BOOL *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetKlDPAFilterClkEn(bValue);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_KL_DPA_FILTER_CLK_EN(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_BOOL *pbValue = (HI_BOOL *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetKlDPAFilterClkEn(pbValue);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_MC_DPA_CLK_SEL_EN(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_BOOL bValue = *(HI_BOOL *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetMcDPAClkSelEn(bValue);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_MC_DPA_CLK_SEL_EN(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_BOOL *pbValue = (HI_BOOL *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetMcDPAClkSelEn(pbValue);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_PVR_DPA_FILTER_CLK_EN(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_BOOL bValue = *(HI_BOOL *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetPvrDPAFilterClkEn(bValue);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_PVR_DPA_FILTER_CLK_EN(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_BOOL *pbValue = (HI_BOOL *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetPvrDPAFilterClkEn(pbValue);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_MISC_LV_SEL(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel = *(HI_UNF_ADVCA_KEYLADDER_LEV_E *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetMiscKlLevel(enLevel);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_MISC_LV_SEL(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_UNF_ADVCA_KEYLADDER_LEV_E *penValue = (HI_UNF_ADVCA_KEYLADDER_LEV_E *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetMiscKlLevel(penValue);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_OEM_ROOT_KEY(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U8 *pu8OEMRootKey = (HI_U8 *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetOEMRootKey(pu8OEMRootKey);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_SOC_OTP_TZ_EN(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_BOOL bValue = *(HI_BOOL *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetTZEnable(bValue);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_SOC_OTP_TZ_EN(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_BOOL *pbEn = (HI_BOOL *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetTZEnStatus(pbEn);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_OTP_TZ(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    CA_OTP_TZ_DATA_S stOTPSetParam = *(CA_OTP_TZ_DATA_S *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetOTPTzData(&stOTPSetParam);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_OTP_TZ(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    CA_OTP_TZ_DATA_S *pstOTPSetParam = (CA_OTP_TZ_DATA_S *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetOTPTzData(pstOTPSetParam);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_LOCK_OTP_TZ(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_UNF_ADVCA_LOCK_TZ_OTP_PARAM_S stOTPLockParam = *(HI_UNF_ADVCA_LOCK_TZ_OTP_PARAM_S *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_LockOTPTzData(&stOTPLockParam);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_CA_GDRM_CRYPT(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 u32GDRMFlag = 0;
    CA_GDRM_CRYPTPM_S *pstParam = (CA_GDRM_CRYPTPM_S *)pstCmdParam->pu8ParamBuf;

    ret = HAL_ADVCA_V300_CryptGDRM(pstParam->stCACryptParams.ladder, pstParam->stCACryptParams.pDin, pstParam->u32KeyAddr, 1, pstParam->stCACryptParams.enKlTarget);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CA("HAL_ADVCA_V300_CryptGDRM failed, ret: 0x%x\n", ret);
    }
    if (HI_UNF_ADVCA_KEYLADDER_LEV3 == pstParam->stCACryptParams.ladder)
    {
        ret = HAL_ADVCA_V300_GetGDRMFlag(&u32GDRMFlag);
        pstParam->u32GDRMFlag = u32GDRMFlag;
    }

    return ret;
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_CHECKSUM_FLAG(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pu32ChecksumFlag = (HI_U32 *)pstCmdParam->pu8ParamBuf;
    return HAL_ADVCA_V300_GetSecretKeyChecksumFlag(pu32ChecksumFlag);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_CASTATE(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pu32Statte = (HI_U32 *)pstCmdParam->pu8ParamBuf;
    return HAL_ADVCA_V300_GetCAStates(pu32Statte);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_MISC_SETALG(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_UNF_ADVCA_ALG_TYPE_E enMISCAlgType = *(HI_UNF_ADVCA_ALG_TYPE_E *)pstCmdParam->pu8ParamBuf;
    return HAL_ADVCA_V300_SetMiscAlgorithm(enMISCAlgType);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_MISC_GETALG(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_UNF_ADVCA_ALG_TYPE_E *penMISCAlgType = (HI_UNF_ADVCA_ALG_TYPE_E *)pstCmdParam->pu8ParamBuf;
    return HAL_ADVCA_V300_GetMiscAlgorithm(penMISCAlgType);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_MISC_ROOT_KEY(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U8 *pu8MiscRootKey = (HI_U8 *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetMISCRootKey(pu8MiscRootKey);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_ESCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U8 *pu8ESCK = (HI_U8 *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetESCK(pu8ESCK);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_ESCK_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_BOOL *pbLock = (HI_BOOL *)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetESCKLock(pbLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_LOCK_RSA_KEY(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_LockRSAKey();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_R2R_ROOT_KEY_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetR2rRootKeyLock();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_R2R_ROOT_KEY_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pR2rRootKeyLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetR2rRootKeyLock(pR2rRootKeyLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_SP_ROOT_KEY_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetSpRootKeyLock();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_SP_ROOT_KEY_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pSpRootKeyLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetSpRootKeyLock(pSpRootKeyLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_DVB_CSA3_ROOT_KEY_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetCsa3RootKeyLock();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_DVB_CSA3_ROOT_KEY_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pCsa3RootKeyLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetCsa3RootKeyLock(pCsa3RootKeyLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_JTAG_KEY_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetJtagKeyLock();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_JTAG_KEY_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pJtagKeyLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetJtagKeyLock(pJtagKeyLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_ID_WORD(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pIdWord = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetIdWord(*pIdWord);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_ID_WORD(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pIdWord = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetIdWord(pIdWord);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_ID_WORD_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetIdWordLock();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_ID_WORD_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pIdWordLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetIdWordLock(pIdWordLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_CSA2_ROOTKEY_CRC(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pCrc = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetCsa2RootKeyCrc(*pCrc);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_CSA2_ROOTKEY_CRC(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pCrc = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetCsa2RootKeyCrc(pCrc);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_CSA2_ROOTKEY_CRC_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetCsa2RootKeyCrcLock();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_CSA2_ROOTKEY_CRC_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetCsa2RootKeyCrcLock(pLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_R2R_ROOTKEY_CRC(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pCrc = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetR2rRootKeyCrc(*pCrc);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_R2R_ROOTKEY_CRC(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pCrc = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetR2rRootKeyCrc(pCrc);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_R2R_ROOTKEY_CRC_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetR2rRootKeyCrcLock();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_R2R_ROOTKEY_CRC_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetR2rRootKeyCrcLock(pLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_SP_ROOTKEY_CRC(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pCrc = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetSpRootKeyCrc(*pCrc);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_SP_ROOTKEY_CRC(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pCrc = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetSpRootKeyCrc(pCrc);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_SP_ROOTKEY_CRC_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetSpRootKeyCrcLock();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_SP_ROOTKEY_CRC_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetSpRootKeyCrcLock(pLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_CSA3_ROOTKEY_CRC(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pCrc = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetCsa3RootKeyCrc(*pCrc);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_CSA3_ROOTKEY_CRC(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pCrc = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetCsa3RootKeyCrc(pCrc);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_CSA3_ROOTKEY_CRC_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetCsa3RootKeyCrcLock();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_CSA3_ROOTKEY_CRC_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetCsa3RootKeyCrcLock(pLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_JTAG_KEY_CRC(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pCrc = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetJtagKeyCrc(*pCrc);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_JTAG_KEY_CRC(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pCrc = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetJtagKeyCrc(pCrc);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_JTAG_KEY_CRC_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetJtagKeyCrcLock();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_JTAG_KEY_CRC_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetJtagKeyCrcLock(pLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_SCS_EN_BAK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pBak = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetScsEnBak(*pBak);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_SCS_EN_BAK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pBak = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetScsEnBak(pBak);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_SCS_EN_BAK_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetScsEnBakLock();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_SCS_EN_BAK_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetScsEnBakLock(pLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_JTAG_MODE_BAK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pBak = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetJtagModeBak(*pBak);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_JTAG_MODE_BAK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pBak = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetJtagModeBak(pBak);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_JTAG_MODE_BAK_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetJtagModeBakLock();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_JTAG_MODE_BAK_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetJtagModeBakLock(pLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_RIGHT_CTRL_EN_BAK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pBak = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetRightCtrlEnBak(*pBak);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_RIGHT_CTRL_EN_BAK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pBak = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetRightCtrlEnBak(pBak);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_RIGHT_CTRL_EN_BAK_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetRightCtrlEnBakLock();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_RIGHT_CTRL_EN_BAK_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetRightCtrlEnBakLock(pLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_MISC_KL_DISABLE(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pDisable = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetMiscKlDisable(*pDisable);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_MISC_KL_DISABLE(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pDisable = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetMiscKlDisable(pDisable);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_MISC_KL_DISABLE_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetMiscKlDisableLock();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_MISC_KL_DISABLE_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetMiscKlDisableLock(pLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_GG_KL_DISABLE(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pDisable = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetGgKlDisable(*pDisable);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_GG_KL_DISABLE(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pDisable = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetGgKlDisable(pDisable);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_GG_KL_DISABLE_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetGgKlDisableLock();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_GG_KL_DISABLE_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetGgKlDisableLock(pLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_BOOT_INFO_DISABLE(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetBootInfoDisable();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_BOOT_INFO_DISABLE(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pDisable = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetBootInfoDisable(pDisable);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_CHECKSUM_READ_DISABLE(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    return DRV_CA_OTP_V200_SetChecksumReadDisable();
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_CHECKSUM_READ_DISABLE(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pDisable = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetChecksumReadDisable(pDisable);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_SELF_BOOT_DISABLE_BAK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pBak = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetSelfBootDisableBak(*pBak);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_SELF_BOOT_DISABLE_BAK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pBak = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetSelfBootDisableBak(pBak);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_TZ_AREA_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetTzAreaLock(*pLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_TZ_AREA_LOCK(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pLock = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetTzAreaLock(pLock);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_BOOTMODE_0(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_UNF_ADVCA_FLASH_TYPE_E BootMode = *(HI_UNF_ADVCA_FLASH_TYPE_E*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetBootMode_0(BootMode);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_BOOTMODE_0(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_UNF_ADVCA_FLASH_TYPE_E *pBootMode = (HI_UNF_ADVCA_FLASH_TYPE_E*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetBootMode_0((CA_OTP_FLASH_TYPE_E *)pBootMode);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_SET_BOOTMODE_1(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 BootMode = *(HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_SetBootMode_1(BootMode);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_GET_BOOTMODE_1(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 *pBootMode = (HI_U32*)pstCmdParam->pu8ParamBuf;
    return DRV_CA_OTP_V200_GetBootMode_1((CA_OTP_FLASH_TYPE_E *)pBootMode);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_LOCK_MISC_KL_DISABLE(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 u32MiscKlDisable = 1;
    return DRV_CA_OTP_V200_SetMiscKLDisable(u32MiscKlDisable);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_LOCK_GG_KL_DISABLE(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 u32GgKlDisable = 1;
    return DRV_CA_OTP_V200_SetGgKLDisable(u32GgKlDisable);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_LOCK_TSKL_CSA3_DISABLE(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 u32TsklCsa3Disable = 1;
    return DRV_CA_OTP_V200_SetTsklCsa3Disable(u32TsklCsa3Disable);
}

static HI_S32 DRV_ADVCA_Ioctl_Child_OTP_READ_BYTE(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    HI_U32 Addr = *(HI_U32 *)(pstCmdParam->pu8ParamBuf);
    pstCmdParam->pu8ParamBuf[4] = DRV_CA_OTP_V200_ReadByte(Addr);
    return HI_SUCCESS;
}

static DRV_ADVCA_IOCTL_CHILD_FUNC_MAP_S g_astIoctlChildFuncMap[] =
{
    {CMD_CHILD_ID_GET_VENDOR_ID,                DRV_ADVCA_Ioctl_Child_GET_VENDOR_ID},
    {CMD_CHILD_ID_SET_SOC_OTP_TZ_EN,            DRV_ADVCA_Ioctl_Child_SET_SOC_OTP_TZ_EN},
    {CMD_CHILD_ID_GET_SOC_OTP_TZ_EN,            DRV_ADVCA_Ioctl_Child_GET_SOC_OTP_TZ_EN},
    {CMD_CHILD_ID_SET_KL_DPA_CLK_SEL_EN,        DRV_ADVCA_Ioctl_Child_SET_KL_DPA_CLK_SEL_EN},
    {CMD_CHILD_ID_GET_KL_DPA_CLK_SEL_EN,        DRV_ADVCA_Ioctl_Child_GET_KL_DPA_CLK_SEL_EN},
    {CMD_CHILD_ID_SET_KL_DPA_FILTER_CLK_EN,     DRV_ADVCA_Ioctl_Child_SET_KL_DPA_FILTER_CLK_EN},
    {CMD_CHILD_ID_GET_KL_DPA_FILTER_CLK_EN,     DRV_ADVCA_Ioctl_Child_GET_KL_DPA_FILTER_CLK_EN},
    {CMD_CHILD_ID_SET_MC_DPA_CLK_SEL_EN,        DRV_ADVCA_Ioctl_Child_SET_MC_DPA_CLK_SEL_EN},
    {CMD_CHILD_ID_GET_MC_DPA_CLK_SEL_EN,        DRV_ADVCA_Ioctl_Child_GET_MC_DPA_CLK_SEL_EN},
    {CMD_CHILD_ID_SET_PVR_DPA_FILTER_CLK_EN,    DRV_ADVCA_Ioctl_Child_SET_PVR_DPA_FILTER_CLK_EN},
    {CMD_CHILD_ID_GET_PVR_DPA_FILTER_CLK_EN,    DRV_ADVCA_Ioctl_Child_GET_PVR_DPA_FILTER_CLK_EN},
    {CMD_CHILD_ID_SET_MISC_LV_SEL,              DRV_ADVCA_Ioctl_Child_SET_MISC_LV_SEL},
    {CMD_CHILD_ID_GET_MISC_LV_SEL,              DRV_ADVCA_Ioctl_Child_GET_MISC_LV_SEL},
    {CMD_CHILD_ID_SET_OEM_ROOT_KEY,             DRV_ADVCA_Ioctl_Child_SET_OEM_ROOT_KEY},
    {CMD_CHILD_ID_GET_OEM_ROOT_KEY,             HI_NULL},
    {CMD_CHILD_ID_GET_OEM_ROOT_KEY_LOCK,        HI_NULL},
    {CMD_CHILD_ID_SET_OTP_TZ,                   DRV_ADVCA_Ioctl_Child_SET_OTP_TZ},
    {CMD_CHILD_ID_GET_OTP_TZ,                   DRV_ADVCA_Ioctl_Child_GET_OTP_TZ},
    {CMD_CHILD_ID_LOCK_OTP_TZ,                  DRV_ADVCA_Ioctl_Child_LOCK_OTP_TZ},
    {CMD_CHILD_ID_CA_GDRM_CRYPT,                DRV_ADVCA_Ioctl_Child_CA_GDRM_CRYPT},
    {CMD_CHILD_ID_GET_CHECKSUM_FLAG,            DRV_ADVCA_Ioctl_Child_GET_CHECKSUM_FLAG},
    {CMD_CHILD_ID_GET_CASTATE,                  DRV_ADVCA_Ioctl_Child_GET_CASTATE},
    {CMD_CHILD_ID_MISC_SETALG,                  DRV_ADVCA_Ioctl_Child_MISC_SETALG},
    {CMD_CHILD_ID_MISC_GETALG,                  DRV_ADVCA_Ioctl_Child_MISC_GETALG},
    {CMD_CHILD_ID_SET_MISC_ROOT_KEY,            DRV_ADVCA_Ioctl_Child_SET_MISC_ROOT_KEY},
    {CMD_CHILD_ID_GET_MISC_ROOT_KEY,            HI_NULL},
    {CMD_CHILD_ID_GET_MISC_ROOT_KEY_LOCK,       HI_NULL},
    {CMD_CHILD_ID_SET_ESCK,                     DRV_ADVCA_Ioctl_Child_SET_ESCK},
    {CMD_CHILD_ID_GET_ESCK,                     HI_NULL},
    {CMD_CHILD_ID_GET_ESCK_LOCK,                DRV_ADVCA_Ioctl_Child_GET_ESCK_LOCK},
    {CMD_CHILD_ID_SET_KEYLADDER_SESSION_KEY,    HI_NULL},
    {CMD_CHILD_ID_LOCK_RSA_KEY,                 DRV_ADVCA_Ioctl_Child_LOCK_RSA_KEY},
    {CMD_CHILD_ID_SET_R2R_ROOT_KEY_LOCK,        DRV_ADVCA_Ioctl_Child_SET_R2R_ROOT_KEY_LOCK},
    {CMD_CHILD_ID_GET_R2R_ROOT_KEY_LOCK,        DRV_ADVCA_Ioctl_Child_GET_R2R_ROOT_KEY_LOCK},
    {CMD_CHILD_ID_SET_SP_ROOT_KEY_LOCK,         DRV_ADVCA_Ioctl_Child_SET_SP_ROOT_KEY_LOCK},
    {CMD_CHILD_ID_GET_SP_ROOT_KEY_LOCK,         DRV_ADVCA_Ioctl_Child_GET_SP_ROOT_KEY_LOCK},
    {CMD_CHILD_ID_SET_DVB_CSA3_ROOT_KEY_LOCK,   DRV_ADVCA_Ioctl_Child_SET_DVB_CSA3_ROOT_KEY_LOCK},
    {CMD_CHILD_ID_GET_DVB_CSA3_ROOT_KEY_LOCK,   DRV_ADVCA_Ioctl_Child_GET_DVB_CSA3_ROOT_KEY_LOCK},
    {CMD_CHILD_ID_SET_JTAG_KEY_LOCK,            DRV_ADVCA_Ioctl_Child_SET_JTAG_KEY_LOCK},
    {CMD_CHILD_ID_GET_JTAG_KEY_LOCK,            DRV_ADVCA_Ioctl_Child_GET_JTAG_KEY_LOCK},
    {CMD_CHILD_ID_SET_ID_WORD,                  DRV_ADVCA_Ioctl_Child_SET_ID_WORD},
    {CMD_CHILD_ID_GET_ID_WORD,                  DRV_ADVCA_Ioctl_Child_GET_ID_WORD},
    {CMD_CHILD_ID_SET_ID_WORD_LOCK,             DRV_ADVCA_Ioctl_Child_SET_ID_WORD_LOCK},
    {CMD_CHILD_ID_GET_ID_WORD_LOCK,             DRV_ADVCA_Ioctl_Child_GET_ID_WORD_LOCK},
    {CMD_CHILD_ID_SET_CSA2_ROOTKEY_CRC,         DRV_ADVCA_Ioctl_Child_SET_CSA2_ROOTKEY_CRC},
    {CMD_CHILD_ID_GET_CSA2_ROOTKEY_CRC,         DRV_ADVCA_Ioctl_Child_GET_CSA2_ROOTKEY_CRC},
    {CMD_CHILD_ID_SET_CSA2_ROOTKEY_CRC_LOCK,    DRV_ADVCA_Ioctl_Child_SET_CSA2_ROOTKEY_CRC_LOCK},
    {CMD_CHILD_ID_GET_CSA2_ROOTKEY_CRC_LOCK,    DRV_ADVCA_Ioctl_Child_GET_CSA2_ROOTKEY_CRC_LOCK},
    {CMD_CHILD_ID_SET_R2R_ROOTKEY_CRC,          DRV_ADVCA_Ioctl_Child_SET_R2R_ROOTKEY_CRC},
    {CMD_CHILD_ID_GET_R2R_ROOTKEY_CRC,          DRV_ADVCA_Ioctl_Child_GET_R2R_ROOTKEY_CRC},
    {CMD_CHILD_ID_SET_R2R_ROOTKEY_CRC_LOCK,     DRV_ADVCA_Ioctl_Child_SET_R2R_ROOTKEY_CRC_LOCK},
    {CMD_CHILD_ID_GET_R2R_ROOTKEY_CRC_LOCK,     DRV_ADVCA_Ioctl_Child_GET_R2R_ROOTKEY_CRC_LOCK},
    {CMD_CHILD_ID_SET_SP_ROOTKEY_CRC,           DRV_ADVCA_Ioctl_Child_SET_SP_ROOTKEY_CRC},
    {CMD_CHILD_ID_GET_SP_ROOTKEY_CRC,           DRV_ADVCA_Ioctl_Child_GET_SP_ROOTKEY_CRC},
    {CMD_CHILD_ID_SET_SP_ROOTKEY_CRC_LOCK,      DRV_ADVCA_Ioctl_Child_SET_SP_ROOTKEY_CRC_LOCK},
    {CMD_CHILD_ID_GET_SP_ROOTKEY_CRC_LOCK,      DRV_ADVCA_Ioctl_Child_GET_SP_ROOTKEY_CRC_LOCK},
    {CMD_CHILD_ID_SET_CSA3_ROOTKEY_CRC,         DRV_ADVCA_Ioctl_Child_SET_CSA3_ROOTKEY_CRC},
    {CMD_CHILD_ID_GET_CSA3_ROOTKEY_CRC,         DRV_ADVCA_Ioctl_Child_GET_CSA3_ROOTKEY_CRC},
    {CMD_CHILD_ID_SET_CSA3_ROOTKEY_CRC_LOCK,    DRV_ADVCA_Ioctl_Child_SET_CSA3_ROOTKEY_CRC_LOCK},
    {CMD_CHILD_ID_GET_CSA3_ROOTKEY_CRC_LOCK,    DRV_ADVCA_Ioctl_Child_GET_CSA3_ROOTKEY_CRC_LOCK},
    {CMD_CHILD_ID_SET_JTAG_KEY_CRC,             DRV_ADVCA_Ioctl_Child_SET_JTAG_KEY_CRC},
    {CMD_CHILD_ID_GET_JTAG_KEY_CRC,             DRV_ADVCA_Ioctl_Child_GET_JTAG_KEY_CRC},
    {CMD_CHILD_ID_SET_JTAG_KEY_CRC_LOCK,        DRV_ADVCA_Ioctl_Child_SET_JTAG_KEY_CRC_LOCK},
    {CMD_CHILD_ID_GET_JTAG_KEY_CRC_LOCK,        DRV_ADVCA_Ioctl_Child_GET_JTAG_KEY_CRC_LOCK},
    {CMD_CHILD_ID_SET_SCS_EN_BAK,               DRV_ADVCA_Ioctl_Child_SET_SCS_EN_BAK},
    {CMD_CHILD_ID_GET_SCS_EN_BAK,               DRV_ADVCA_Ioctl_Child_GET_SCS_EN_BAK},
    {CMD_CHILD_ID_SET_SCS_EN_BAK_LOCK,          DRV_ADVCA_Ioctl_Child_SET_SCS_EN_BAK_LOCK},
    {CMD_CHILD_ID_GET_SCS_EN_BAK_LOCK,          DRV_ADVCA_Ioctl_Child_GET_SCS_EN_BAK_LOCK},
    {CMD_CHILD_ID_SET_JTAG_MODE_BAK,            DRV_ADVCA_Ioctl_Child_SET_JTAG_MODE_BAK},
    {CMD_CHILD_ID_GET_JTAG_MODE_BAK,            DRV_ADVCA_Ioctl_Child_GET_JTAG_MODE_BAK},
    {CMD_CHILD_ID_SET_JTAG_MODE_BAK_LOCK,       DRV_ADVCA_Ioctl_Child_SET_JTAG_MODE_BAK_LOCK},
    {CMD_CHILD_ID_GET_JTAG_MODE_BAK_LOCK,       DRV_ADVCA_Ioctl_Child_GET_JTAG_MODE_BAK_LOCK},
    {CMD_CHILD_ID_SET_RIGHT_CTRL_EN_BAK,        DRV_ADVCA_Ioctl_Child_SET_RIGHT_CTRL_EN_BAK},
    {CMD_CHILD_ID_GET_RIGHT_CTRL_EN_BAK,        DRV_ADVCA_Ioctl_Child_GET_RIGHT_CTRL_EN_BAK},
    {CMD_CHILD_ID_SET_RIGHT_CTRL_EN_BAK_LOCK,   DRV_ADVCA_Ioctl_Child_SET_RIGHT_CTRL_EN_BAK_LOCK},
    {CMD_CHILD_ID_GET_RIGHT_CTRL_EN_BAK_LOCK,   DRV_ADVCA_Ioctl_Child_GET_RIGHT_CTRL_EN_BAK_LOCK},
    {CMD_CHILD_ID_SET_MISC_KL_DISABLE,          DRV_ADVCA_Ioctl_Child_SET_MISC_KL_DISABLE},
    {CMD_CHILD_ID_GET_MISC_KL_DISABLE,          DRV_ADVCA_Ioctl_Child_GET_MISC_KL_DISABLE},
    {CMD_CHILD_ID_SET_MISC_KL_DISABLE_LOCK,     DRV_ADVCA_Ioctl_Child_SET_MISC_KL_DISABLE_LOCK},
    {CMD_CHILD_ID_GET_MISC_KL_DISABLE_LOCK,     DRV_ADVCA_Ioctl_Child_GET_MISC_KL_DISABLE_LOCK},
    {CMD_CHILD_ID_SET_GG_KL_DISABLE,            DRV_ADVCA_Ioctl_Child_SET_GG_KL_DISABLE},
    {CMD_CHILD_ID_GET_GG_KL_DISABLE,            DRV_ADVCA_Ioctl_Child_GET_GG_KL_DISABLE},
    {CMD_CHILD_ID_SET_GG_KL_DISABLE_LOCK,       DRV_ADVCA_Ioctl_Child_SET_GG_KL_DISABLE_LOCK},
    {CMD_CHILD_ID_GET_GG_KL_DISABLE_LOCK,       DRV_ADVCA_Ioctl_Child_GET_GG_KL_DISABLE_LOCK},
    {CMD_CHILD_ID_SET_BOOT_INFO_DISABLE,        DRV_ADVCA_Ioctl_Child_SET_BOOT_INFO_DISABLE},
    {CMD_CHILD_ID_GET_BOOT_INFO_DISABLE,        DRV_ADVCA_Ioctl_Child_GET_BOOT_INFO_DISABLE},
    {CMD_CHILD_ID_SET_CHECKSUM_READ_DISABLE,    DRV_ADVCA_Ioctl_Child_SET_CHECKSUM_READ_DISABLE},
    {CMD_CHILD_ID_GET_CHECKSUM_READ_DISABLE,    DRV_ADVCA_Ioctl_Child_GET_CHECKSUM_READ_DISABLE},
    {CMD_CHILD_ID_SET_SELF_BOOT_DISABLE_BAK,    DRV_ADVCA_Ioctl_Child_SET_SELF_BOOT_DISABLE_BAK},
    {CMD_CHILD_ID_GET_SELF_BOOT_DISABLE_BAK,    DRV_ADVCA_Ioctl_Child_GET_SELF_BOOT_DISABLE_BAK},
    {CMD_CHILD_ID_SET_TZ_AREA_LOCK,             DRV_ADVCA_Ioctl_Child_SET_TZ_AREA_LOCK},
    {CMD_CHILD_ID_GET_TZ_AREA_LOCK,             DRV_ADVCA_Ioctl_Child_GET_TZ_AREA_LOCK},
    {CMD_CHILD_ID_SET_BOOTMODE_0,               DRV_ADVCA_Ioctl_Child_SET_BOOTMODE_0},
    {CMD_CHILD_ID_GET_BOOTMODE_0,               DRV_ADVCA_Ioctl_Child_GET_BOOTMODE_0},
    {CMD_CHILD_ID_SET_BOOTMODE_1,               DRV_ADVCA_Ioctl_Child_SET_BOOTMODE_1},
    {CMD_CHILD_ID_GET_BOOTMODE_1,               DRV_ADVCA_Ioctl_Child_GET_BOOTMODE_1},
    {CMD_CHILD_ID_LOCK_MISC_KL_DISABLE,         DRV_ADVCA_Ioctl_Child_LOCK_MISC_KL_DISABLE},
    {CMD_CHILD_ID_LOCK_GG_KL_DISABLE,           DRV_ADVCA_Ioctl_Child_LOCK_GG_KL_DISABLE},
    {CMD_CHILD_ID_LOCK_TSKL_CSA3_DISABLE,       DRV_ADVCA_Ioctl_Child_LOCK_TSKL_CSA3_DISABLE},
    {CMD_CHILD_ID_OTP_READ_BYTE,                DRV_ADVCA_Ioctl_Child_OTP_READ_BYTE},
};

static HI_S32 DRV_ADVCA_V300_Ioctl_Child(CA_CMD_SUPPER_ID_S *pstCmdParam)
{
    if (NULL == pstCmdParam)
    {
        HI_ERR_CA("Null pointer input!\n");
        return HI_FAILURE;
    }
    if (pstCmdParam->enCmdChildID >= CMD_CHILD_ID_BUTT)
    {
        HI_ERR_CA("invalid cmd ID: %d\n", pstCmdParam->enCmdChildID);
        return HI_FAILURE;
    }
    if (HI_NULL == g_astIoctlChildFuncMap[pstCmdParam->enCmdChildID].pfnIoctlChild)
    {
        HI_ERR_CA("not support cmd ID: %d\n", pstCmdParam->enCmdChildID);
        return HI_FAILURE;
    }

    return g_astIoctlChildFuncMap[pstCmdParam->enCmdChildID].pfnIoctlChild(pstCmdParam);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_CHIPID(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 u32VendorId = 0;
    HI_U8 au8IDBuf[4] = {0};
    HI_U32 *pu32ChipId = (HI_U32*)arg;

    if (HI_NULL == pu32ChipId)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }

    ret = DRV_CA_OTP_V200_GetVendorId((CA_OTP_VENDOR_TYPE_E *)&u32VendorId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("get vendor type failed, ret: 0x%x\n", ret);
        return ret;
    }

    if ((CA_OTP_VENDOR_CONAX == u32VendorId) || (CA_OTP_VENDOR_NAGRA == u32VendorId))
    {
        ret = DRV_CA_OTP_V200_GetChipId(pu32ChipId);
    }
    else
    {
        memset(au8IDBuf, 0x0, 4);
        ret = DRV_CA_OTP_V200_GetUniqueChipId(au8IDBuf);
        *pu32ChipId = (au8IDBuf[0]<<24) + (au8IDBuf[1]<<16) + (au8IDBuf[2]<<8) + au8IDBuf[3];
    }

    return ret;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_MARKETID(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 u32VendorId = 0;
    HI_U8 au8IDBuf[4] = {0};

    ret = DRV_CA_OTP_V200_GetVendorId((CA_OTP_VENDOR_TYPE_E *)&u32VendorId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("get vendor type failed, ret: 0x%x\n", ret);
        return ret;
    }

    if (CA_OTP_VENDOR_NAGRA == u32VendorId)
    {
        HI_U32 u32MaketId;

        if (HI_NULL == arg)
        {
            HI_ERR_CA("invalid arg\n");
            return HI_FAILURE;
        }
        u32MaketId = *(HI_U32*)arg;
        ret = DRV_CA_OTP_V200_Set_MarketId(u32MaketId);
    }
    else
    {
        CA_KEY_S *pKey = (CA_KEY_S*)arg;

        if (HI_NULL == pKey)
        {
            HI_ERR_CA("invalid arg\n");
            return HI_FAILURE;
        }
        memset(au8IDBuf, 0x0, 4);
        au8IDBuf[0] = pKey->KeyBuf[3];
        au8IDBuf[1] = pKey->KeyBuf[2];
        au8IDBuf[2] = pKey->KeyBuf[1];
        au8IDBuf[3] = pKey->KeyBuf[0];
        ret = DRV_CA_OTP_V200_Set_UniqueMarketId(au8IDBuf);
    }

    return ret;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_MARKETID(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 u32VendorId = 0;
    HI_U8 au8IDBuf[4] = {0};

    ret = DRV_CA_OTP_V200_GetVendorId((CA_OTP_VENDOR_TYPE_E *)&u32VendorId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("get vendor type failed, ret: 0x%x\n", ret);
        return ret;
    }

    if (CA_OTP_VENDOR_NAGRA == u32VendorId)
    {
        HI_U32 *pu32MarketId = (HI_U32*)arg;

        if (HI_NULL == pu32MarketId)
        {
            HI_ERR_CA("invalid arg\n");
            return HI_FAILURE;
        }
        ret = DRV_CA_OTP_V200_MarketId(pu32MarketId);
    }
    else
    {
        CA_KEY_S *pKey = (CA_KEY_S*)arg;

        if (HI_NULL == pKey)
        {
            HI_ERR_CA("invalid arg\n");
            return HI_FAILURE;
        }
        memset(au8IDBuf, 0x0, 4);
        ret = DRV_CA_OTP_V200_Get_UniqueMarketId(au8IDBuf);
        pKey->KeyBuf[0] = au8IDBuf[3];
        pKey->KeyBuf[1] = au8IDBuf[2];
        pKey->KeyBuf[2] = au8IDBuf[1];
        pKey->KeyBuf[3] = au8IDBuf[0];
    }

    return ret;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_STBSN(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 u32VendorId = 0;
    HI_U8 au8IDBuf[4] = {0};

    ret = DRV_CA_OTP_V200_GetVendorId((CA_OTP_VENDOR_TYPE_E *)&u32VendorId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("get vendor type failed, ret: 0x%x\n", ret);
        return ret;
    }

    if (CA_OTP_VENDOR_NAGRA == u32VendorId)
    {
        HI_U32 u32StbSN;

        if (HI_NULL == arg)
        {
            HI_ERR_CA("invalid arg\n");
            return HI_FAILURE;
        }
        u32StbSN = *(HI_U32*)arg;
        ret = DRV_CA_OTP_V200_Set_STBSN(u32StbSN);
    }
    else
    {
        CA_KEY_S *pKey = (CA_KEY_S*)arg;

        if (HI_NULL == pKey)
        {
            HI_ERR_CA("invalid arg\n");
            return HI_FAILURE;
        }
        memset(au8IDBuf, 0x0, 4);
        au8IDBuf[0] = pKey->KeyBuf[3];
        au8IDBuf[1] = pKey->KeyBuf[2];
        au8IDBuf[2] = pKey->KeyBuf[1];
        au8IDBuf[3] = pKey->KeyBuf[0];
        ret = DRV_CA_OTP_V200_Set_UniqueSTBSN(au8IDBuf);
    }

    return ret;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_STBSN(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 u32VendorId = 0;
    HI_U8 au8IDBuf[4] = {0};

    ret = DRV_CA_OTP_V200_GetVendorId((CA_OTP_VENDOR_TYPE_E *)&u32VendorId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("get vendor type failed, ret: 0x%x\n", ret);
        return ret;
    }

    if (CA_OTP_VENDOR_NAGRA == u32VendorId)
    {
        HI_U32 *pu32StbSN = (HI_U32*)arg;

        if (HI_NULL == pu32StbSN)
        {
            HI_ERR_CA("invalid arg\n");
             return HI_FAILURE;
        }
        ret = DRV_CA_OTP_V200_GetSTBSN(pu32StbSN);
    }
    else
    {
        CA_KEY_S *pKey = (CA_KEY_S*)arg;

        if (HI_NULL == pKey)
        {
            HI_ERR_CA("invalid arg\n");
             return HI_FAILURE;
        }
        memset(au8IDBuf, 0x0, 4);
        ret = DRV_CA_OTP_V200_Get_UniqueSTBSN(au8IDBuf);
        pKey->KeyBuf[0] = au8IDBuf[3];
        pKey->KeyBuf[1] = au8IDBuf[2];
        pKey->KeyBuf[2] = au8IDBuf[1];
        pKey->KeyBuf[3] = au8IDBuf[0];
    }

    return ret;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_VERSIONID(HI_VOID* arg)
{
    CA_KEY_S *pKey = (CA_KEY_S*)arg;
    HI_U8 au8IDBuf[4] = {0};

    if (HI_NULL == pKey)
    {
        HI_ERR_CA("invalid arg\n");
         return HI_FAILURE;
    }
    memset(au8IDBuf, 0x0, 4);
    au8IDBuf[0] = pKey->KeyBuf[3];
    au8IDBuf[1] = pKey->KeyBuf[2];
    au8IDBuf[2] = pKey->KeyBuf[1];
    au8IDBuf[3] = pKey->KeyBuf[0];
    return DRV_CA_OTP_V200_Set_UniqueVersionId(au8IDBuf);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_VERSIONID(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    CA_KEY_S *pKey = (CA_KEY_S*)arg;
    HI_U8 au8IDBuf[4] = {0};

    if (HI_NULL == pKey)
    {
        HI_ERR_CA("invalid arg\n");
         return HI_FAILURE;
    }
    memset(au8IDBuf, 0x0, 4);
    ret = DRV_CA_OTP_V200_Get_UniqueVersionId(au8IDBuf);
    pKey->KeyBuf[0] = au8IDBuf[3];
    pKey->KeyBuf[1] = au8IDBuf[2];
    pKey->KeyBuf[2] = au8IDBuf[1];
    pKey->KeyBuf[3] = au8IDBuf[0];

    return ret;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_LOCKHARDCWSEL(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_LockHardCwSel();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_LOCKBOOTDECEN(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetBloadDecEn(1);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_LOCKR2RHARDKEY(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_LockR2RHardKey();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_STATHARDCWSEL (HI_VOID* arg)
{
    HI_U32 *pbLock = (HI_U32*)arg;

    if (HI_NULL == pbLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_StatHardCwSel(pbLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_STATR2RHARDKEY (HI_VOID* arg)
{
    HI_U32 *pbLock = (HI_U32*)arg;

    if (HI_NULL == pbLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_StatR2RHardKey(pbLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_STATTDESLOCK (HI_VOID* arg)
{
    HI_U32 *pbLock = (HI_U32*)arg;

    if (HI_NULL == pbLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetTdesLock(pbLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_DISABLELPT(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_DisableLinkProtect();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_DISABLESELFBOOT(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_DisableSelfBoot(1);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SELFBOOT(HI_VOID* arg)
{
    HI_U32 *pu32DisableSelfBoot = (HI_U32 *)arg;

    if (HI_NULL == pu32DisableSelfBoot)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_DisableSelfBoot(*pu32DisableSelfBoot);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BOOTMODE(HI_VOID* arg)
{
    HI_UNF_ADVCA_FLASH_TYPE_E BootMode;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    BootMode = *(HI_UNF_ADVCA_FLASH_TYPE_E*)arg;
    return DRV_CA_OTP_V200_SetBootMode((CA_OTP_FLASH_TYPE_E)BootMode);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BOOTMODE(HI_VOID* arg)
{
    HI_UNF_ADVCA_FLASH_TYPE_E *pBootMode = (HI_UNF_ADVCA_FLASH_TYPE_E *)arg;

    if (HI_NULL == pBootMode)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetBootMode(pBootMode);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SCSACTIVE(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetSCSActive();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_SCSACTIVE(HI_VOID* arg)
{
    HI_U32 *pu32SecBoot = (HI_U32*)arg;

    if (HI_NULL == pu32SecBoot)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetSCSActive(pu32SecBoot);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_JTAGPRTMODE(HI_VOID* arg)
{
    HI_UNF_ADVCA_JTAG_MODE_E JtagMode;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    JtagMode = *(HI_UNF_ADVCA_JTAG_MODE_E*)arg;
    return DRV_CA_OTP_V200_SetJtagProtectMode(JtagMode);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_JTAGPRTMODE(HI_VOID* arg)
{
    HI_UNF_ADVCA_JTAG_MODE_E *pJtagMode = (HI_UNF_ADVCA_JTAG_MODE_E*)arg;

    if (HI_NULL == pJtagMode)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetJtagProtectMode((CA_OTP_JTAG_MODE_E *)pJtagMode);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_SETLADDER(HI_VOID* arg)
{
    HI_UNF_ADVCA_KEYLADDER_LEV_E DvbLadder;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    DvbLadder = *(HI_UNF_ADVCA_KEYLADDER_LEV_E*)arg;
    return HAL_ADVCA_V300_SetCWLadderLevel(DvbLadder);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_GETLADDER(HI_VOID* arg)
{
    HI_UNF_ADVCA_KEYLADDER_LEV_E *pDvbLadder = (HI_UNF_ADVCA_KEYLADDER_LEV_E*)arg;

    if (HI_NULL == pDvbLadder)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_GetCWLadderLevel(pDvbLadder);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_R2R_SETLADDER(HI_VOID* arg)
{
    HI_UNF_ADVCA_KEYLADDER_LEV_E R2RLadder;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    R2RLadder = *(HI_UNF_ADVCA_KEYLADDER_LEV_E*)arg;
    return HAL_ADVCA_V300_SetR2RLadderLevel(R2RLadder);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_R2R_GETLADDER(HI_VOID* arg)
{
    HI_UNF_ADVCA_KEYLADDER_LEV_E *pR2RLadder = (HI_UNF_ADVCA_KEYLADDER_LEV_E*)arg;

    if (HI_NULL == pR2RLadder)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_GetR2RLadderLevel(pR2RLadder);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SP_SETLADDER(HI_VOID* arg)
{
    HI_UNF_ADVCA_KEYLADDER_LEV_E SPLadder;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    SPLadder = *(HI_UNF_ADVCA_KEYLADDER_LEV_E*)arg;
    return HAL_ADVCA_V300_SetSPLadderLevel(SPLadder);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SP_GETLADDER(HI_VOID* arg)
{
    HI_UNF_ADVCA_KEYLADDER_LEV_E *pSPLadder = (HI_UNF_ADVCA_KEYLADDER_LEV_E*)arg;

    if (HI_NULL == pSPLadder)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_GetSPLadderLevel(pSPLadder);
}

// TODO: Need set? Now fix on TDEA
static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_SETALG(HI_VOID* arg)
{
    HI_UNF_ADVCA_ALG_TYPE_E CwAlgType;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    CwAlgType = *(HI_U32*)arg;
    return HAL_ADVCA_V300_SetCWAlgorithm(CwAlgType);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_CSA3_SETALG(HI_VOID* arg)
{
    HI_UNF_ADVCA_ALG_TYPE_E Csa3AlgType;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    Csa3AlgType = *(HI_U32*)arg;
    return HAL_ADVCA_V300_SetCSA3Algorithm(Csa3AlgType);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_R2R_SETALG(HI_VOID* arg)
{
    HI_UNF_ADVCA_ALG_TYPE_E R2RType;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    R2RType = *(HI_U32*)arg;
    return HAL_ADVCA_V300_SetR2RAlgorithm(R2RType);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SP_SETALG(HI_VOID* arg)
{
    HI_UNF_ADVCA_ALG_TYPE_E eSPType;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    eSPType = *(HI_U32*)arg;
    return HAL_ADVCA_V300_SetSPAlgorithm(eSPType);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SP_SET_DSC_MODE(HI_VOID* arg)
{
    HI_UNF_ADVCA_SP_DSC_MODE_E eSPDscMode;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    eSPDscMode = *(HI_UNF_ADVCA_SP_DSC_MODE_E*)arg;
    return HAL_ADVCA_V300_SetSPDscMode(eSPDscMode);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_GETALG(HI_VOID* arg)
{
    HI_U32 *pu32CwAlgType = (HI_U32*)arg;

    if (HI_NULL == pu32CwAlgType)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_GetCWAlgorithm(pu32CwAlgType);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_CSA3_GETALG(HI_VOID* arg)
{
    HI_U32 *pu32Csa3AlgType = (HI_U32*)arg;

    if (HI_NULL == pu32Csa3AlgType)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }

    return HAL_ADVCA_V300_GetCSA3Algorithm(pu32Csa3AlgType);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_R2R_GETALG(HI_VOID* arg)
{
    HI_U32 *pu32R2RAlgType = (HI_U32*)arg;

    if (HI_NULL == pu32R2RAlgType)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_GetR2RAlgorithm(pu32R2RAlgType);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SP_GETALG(HI_VOID* arg)
{
    HI_UNF_ADVCA_ALG_TYPE_E *penSPAlgType = (HI_UNF_ADVCA_ALG_TYPE_E*)arg;

    if (HI_NULL == penSPAlgType)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_GetSPAlgorithm(penSPAlgType);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SP_GET_DSC_MODE(HI_VOID* arg)
{
    HI_UNF_ADVCA_SP_DSC_MODE_E *penSPDscMode = (HI_UNF_ADVCA_SP_DSC_MODE_E*)arg;

    if (HI_NULL == penSPDscMode)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_GetSPDscMode(penSPDscMode);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_CRYPT(HI_VOID* arg)
{
    CA_CRYPTPM_S *pCryptParam = (CA_CRYPTPM_S*)arg;

    //It is to set DVB Chipset Pairing level 1 Input
    if (HI_NULL == pCryptParam)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_DecryptCw(pCryptParam->ladder,pCryptParam->pDin,0,0);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_R2R_CRYPT(HI_VOID* arg)
{
    CA_CRYPTPM_S *pCryptParam = (CA_CRYPTPM_S*)arg;

    //It is to set Cipher level 1 Input
    if (HI_NULL == pCryptParam)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_CryptR2R(pCryptParam->ladder,pCryptParam->pDin,0,1);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SP_CRYPT(HI_VOID* arg)
{
    CA_CRYPTPM_S *pCryptParam = (CA_CRYPTPM_S*)arg;

    //It is to set Cipher level 1 Input
    if (HI_NULL == pCryptParam)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_DecryptSP(pCryptParam->ladder,pCryptParam->pDin,0,0,0);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_CSA3_CRYPT(HI_VOID* arg)
{
    CA_CRYPTPM_S *pCryptParam = (CA_CRYPTPM_S*)arg;

    //It is to set CSA3 Chipset Pairing level 1 Input
    if (HI_NULL == pCryptParam)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_DecryptCsa3(pCryptParam->ladder,pCryptParam->pDin,0,0);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SWPK_CRYPT (HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    CA_ENCRYPTSWPK_S *pEncryptSwpk = (CA_ENCRYPTSWPK_S*)arg;

    if (HI_NULL == pEncryptSwpk)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
#if defined (CHIP_TYPE_hi3716mv410) || defined (CHIP_TYPE_hi3716mv420) || defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv200_a)
    //use stb rootkey,not set the bload_dec_mode
#else
    /*Set the bload_dec_mode to R2R Rootkey*/
    ret = DRV_CA_OTP_V200_SetBootDecMode(1);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CA("DRV_CA_OTP_V200_SetBootDecMode failed, ret: 0x%x\n", ret);
        return HI_FAILURE;
    }
#endif
    ret = HAL_ADVCA_V300_EncryptSwpk(pEncryptSwpk->ClearSwpk,pEncryptSwpk->EncryptSwpk);
    return ret;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_RSA_KEY_N(HI_VOID* arg)
{
    CA_KEY_S *pKey = (CA_KEY_S*)arg;

    if (HI_NULL == pKey)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_SetRSAKeyN(pKey->KeyBuf);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_RSA_KEY_E(HI_VOID* arg)
{
    CA_KEY_S *pKey = (CA_KEY_S*)arg;

    if (HI_NULL == pKey)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_SetRSAKeyE(pKey->KeyBuf);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_RSA_KEY_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_LockRSAKey();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_DVB_ROOT_KEY(HI_VOID* arg)
{
    CA_KEY_S *pKey = (CA_KEY_S*)arg;

    if (HI_NULL == pKey)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_SetCSA2RootKey(pKey->KeyBuf);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_DVB_CSA3_ROOT_KEY(HI_VOID* arg)
{
    CA_KEY_S *pKey = (CA_KEY_S*)arg;

    if (HI_NULL == pKey)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_SetCSA3RootKey(pKey->KeyBuf);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_R2R_ROOT_KEY(HI_VOID* arg)
{
    CA_KEY_S *pKey = (CA_KEY_S*)arg;

    if (HI_NULL == pKey)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_SetR2RRootKey(pKey->KeyBuf);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SP_ROOT_KEY(HI_VOID* arg)
{
    CA_KEY_S *pKey = (CA_KEY_S*)arg;

    if (HI_NULL == pKey)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_SetSPRootKey(pKey->KeyBuf);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_JTAG_KEY(HI_VOID* arg)
{
    CA_KEY_S *pKey = (CA_KEY_S*)arg;

    if (HI_NULL == pKey)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_SetJtagKey(pKey->KeyBuf);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SECRET_KEY_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetRootKeyLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_CHIPID(HI_VOID* arg)
{
    HI_U32 u32ChipID;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32ChipID = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetChipId(u32ChipID);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_CHIPID_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetChipIdLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_STBSN_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetStbSnLock_0();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_MKTID_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetMktIdLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_VENDOR_ID(HI_VOID* arg)
{
    CA_OTP_VENDOR_TYPE_E vendorType;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    vendorType = *(CA_OTP_VENDOR_TYPE_E*)arg;
    return DRV_CA_OTP_V200_SetVendorId(vendorType);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_VENDOR_ID_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetVendorIdLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_VERSION_ID_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetVersionIdLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BOOT_SEL_LOCK_0(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetBootSelLock_0();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BOOT_SEL_LOCK_1(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetBootSelLock_1();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BLOAD_DEC_EN(HI_VOID* arg)
{
    HI_U32 u32BloadEncDisable;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32BloadEncDisable = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetBloadDecEn(u32BloadEncDisable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BLOAD_DEC_EN_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_LockBootDecEn();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SELFBOOT_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetSelfbootLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_LOWPOWER_DISABLE(HI_VOID* arg)
{
    HI_U32 u32LowPowerDisable;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32LowPowerDisable = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetLowPowerDisable(u32LowPowerDisable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_LOWPOWER_DISABLE_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetLowPowerDisableLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_SETLADDERLOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetDVBLadderLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_CSA3_SETLADDER(HI_VOID* arg)
{
    CA_OTP_KEY_LEVEL_E otpKeyLevel;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    otpKeyLevel = *(CA_OTP_KEY_LEVEL_E*)arg;
    return DRV_CA_OTP_V200_SetCSA3LadderLevel(otpKeyLevel);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_CSA3_SETLADDERLOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetCSA3LadderLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_R2R_SETLADDERLOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetR2RLadderLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SP_SETLADDERLOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetSPLadderLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_LINK_PRT_DISABLE_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_DisableLinkProtect();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_CSA2_HARDONLY_EN_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_LockHardCwSel();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_CSA3_HARDONLY_EN(HI_VOID* arg)
{
    HI_U32 u32CSA3HardOnlyEn;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32CSA3HardOnlyEn = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetTSCSA3HardonlyEn(u32CSA3HardOnlyEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_CSA3_HARDONLY_EN_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetCSA3HardOnlyEnLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SP_HARDONLY_EN(HI_VOID* arg)
{
    HI_U32 u32SPHardOnlyEn;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32SPHardOnlyEn = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetTSSPEHardonlyEn(u32SPHardOnlyEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SP_HARDONLY_EN_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_LockHardSPESel();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TSKL_CSA2_DISABLE(HI_VOID* arg)
{
    HI_U32 u32TsklCSA2Disable;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32TsklCSA2Disable = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetTSCWDeactive(u32TsklCSA2Disable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TSKL_CSA2_DISABLE_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetTSCWDeactiveLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TSKL_CSA3_DISABLE(HI_VOID* arg)
{
    HI_U32 u32TsklCSA3Disable;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32TsklCSA3Disable = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetTSCSA3Deactive(u32TsklCSA3Disable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TSKL_CSA3_DISABLE_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetTSCSA3DeactiveLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TSKL_SP_DISABLE(HI_VOID* arg)
{
    HI_U32 u32TsklSPDisable;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32TsklSPDisable = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetTSSPDeactive(u32TsklSPDisable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TSKL_SP_DISABLE_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetTSSPDeactiveLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TSKL_DES_DISABLE(HI_VOID* arg)
{
    HI_U32 u32TsklDesDisable;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32TsklDesDisable = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetDesDisable(u32TsklDesDisable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TSKL_DES_DISABLE_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetDesDisableLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_MCKL_DES_HARD_DISABLE(HI_VOID* arg)
{
    HI_U32 u32McklDesHardDisable;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32McklDesHardDisable = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetDesHardDisable(u32McklDesHardDisable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_MCKL_DES_HARD_DISABLE_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetDesHardDisableLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BLOAD_MODE_SEL(HI_VOID* arg)
{
    HI_U32 u32BootDecMode;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32BootDecMode = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetBootDecMode(u32BootDecMode);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BLOAD_MODE_SEL_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetBloadModeSelLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_DDR_SCRAMBLE_EN(HI_VOID* arg)
{
    HI_U32 u32DdrScrambleEn;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32DdrScrambleEn = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetDDRScrambleEn(u32DdrScrambleEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_DDR_SCRAMBLE_EN_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetDDRScrambleEnLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_OTP_GLOBAL_LOCK_EN(HI_VOID* arg)
{
    HI_U32 u32OtpGlobalLockEn;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32OtpGlobalLockEn = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetOtpGlobalLockEn(u32OtpGlobalLockEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_OTP_GLOBAL_LOCK_EN_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetOtpGlobalLockEnLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SECURE_CHIP_FLAG(HI_VOID* arg)
{
    HI_U32 u32SecureChipFlag;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32SecureChipFlag = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetSecureChipFlag(u32SecureChipFlag);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SECURE_CHIP_FLAG_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetSecureChipFlagLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_DCAS_KL_DISABLE(HI_VOID* arg)
{
    HI_U32 u32DcasKlDisable;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32DcasKlDisable = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetDcasKLDisable(u32DcasKlDisable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_DCAS_KL_DISABLE_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetDcasKLDisableLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TS_OUT_DISABLE(HI_VOID* arg)
{
    HI_U32 u32TsOutDisable;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32TsOutDisable = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetTsOutDisable(u32TsOutDisable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TS_OUT_DISABLE_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetTsOutDisableLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_LPC_DISABLE(HI_VOID* arg)
{
    HI_U32 u32LpcDisable;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32LpcDisable = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetLpcEn(u32LpcDisable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_LPC_DISABLE_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetLpcEnLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_LPC_MASTER_DISABLE(HI_VOID* arg)
{
    HI_U32 u32LpcMasterDisable;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32LpcMasterDisable = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetLpcMasterEn(u32LpcMasterDisable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_LPC_MASTER_DISABLE_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetLpcMasterEnLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BOOTSEL_CTRL_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetBootSelCtrlLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_RUNTIME_CHECK_EN(HI_VOID* arg)
{
    HI_U32 u32RuntimeCheckEn;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32RuntimeCheckEn = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetRuntimeCheckEn(u32RuntimeCheckEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_RUNTIME_CHECK_EN_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetRuntimeCheckEnLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_WAKEUP_DDR_CHECK_EN(HI_VOID* arg)
{
    HI_U32 u32WakeupDdrCheckEn;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32WakeupDdrCheckEn = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetWakeupDDRCheckEn(u32WakeupDdrCheckEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_WAKEUP_DDR_CHECK_EN_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetWakeupDDRCheckEnLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_VERSION_CHECK_EN(HI_VOID* arg)
{
    HI_U32 u32VersionIdCheckEn;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32VersionIdCheckEn = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetVersionIdCheckEn(u32VersionIdCheckEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_VERSION_CHECK_EN_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetVersionIdCheckEnLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BL_MSID_CHECK_EN(HI_VOID* arg)
{
    HI_U32 u32MsidCheckEn;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32MsidCheckEn = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetBlMSIDCheckEn(u32MsidCheckEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BL_MSID_CHECK_EN_LOCK(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetBlMSIDCheckEnLock();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_JTAG_READ_DISABLE(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetJtagReadDisable();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_JTAG_WRITE_DISABLE(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_DisableJtagWrite();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_DEBUG_DISABLE(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetDebugDisable();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_RIGHT_CTRL_EN(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetRigthCtrlEn();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_RSA_KEY_N(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 au8KeyBuf[512] = {0};
    CA_KEY_S *pKey = (CA_KEY_S*)arg;

    if (HI_NULL == pKey)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    memset(au8KeyBuf, 0x0, 256);
    ret = DRV_CA_OTP_V200_GetRSAKeyN(au8KeyBuf);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CA("DRV_CA_OTP_V200_GetRSAKeyN failed, ret: 0x%x\n", ret);
        return ret;
    }
    memcpy(pKey->KeyBuf, au8KeyBuf, 256);
    return ret;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_RSA_KEY_E(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 au8KeyBuf[512] = {0};
    CA_KEY_S *pKey = (CA_KEY_S*)arg;

    if (HI_NULL == pKey)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    memset(au8KeyBuf, 0x0, 16);
    ret = DRV_CA_OTP_V200_GetRSAKeyE(au8KeyBuf);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CA("DRV_CA_OTP_V200_GetRSAKeyN failed, ret: 0x%x\n", ret);
        return ret;
    }
    memcpy(pKey->KeyBuf, au8KeyBuf, 16);
    return ret;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_RSA_KEY_LOCK(HI_VOID* arg)
{
    HI_U32 *pbLock = (HI_U32*)arg;

    if (HI_NULL == pbLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetRSAKeyLock(pbLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_SECRET_KEY_LOCK(HI_VOID* arg)
{
    HI_U32 *pbLock = (HI_U32*)arg;

    if (HI_NULL == pbLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetRootKeyLock(pbLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_CHIPID_LOCK(HI_VOID* arg)
{
    HI_U32 *pbLock = (HI_U32*)arg;

    if (HI_NULL == pbLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetChipIdLock(pbLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_STBSN_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32StbSnP = (HI_U32*)arg;

    if (HI_NULL == pu32StbSnP)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetStbSnLock_0(pu32StbSnP);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_MKTID_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32MKTKDLock = (HI_U32*)arg;

    if (HI_NULL == pu32MKTKDLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetMktIdLock(pu32MKTKDLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_VENDOR_ID(HI_VOID* arg)
{
    CA_OTP_VENDOR_TYPE_E *penVendorId = (CA_OTP_VENDOR_TYPE_E *)arg;

    if (HI_NULL == penVendorId)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetVendorId(penVendorId);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_VENDOR_ID_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32VendorIdLock = (HI_U32*)arg;

    if (HI_NULL == pu32VendorIdLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetVendorIdLock(pu32VendorIdLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_VERSION_ID_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32Lock = (HI_U32*)arg;

    if (HI_NULL == pu32Lock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetVersionIdCheckLock(pu32Lock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BOOT_SEL_LOCK_0(HI_VOID* arg)
{
    HI_U32 *pu32BootSelLock = (HI_U32*)arg;

    if (HI_NULL == pu32BootSelLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetBootSelLock_0(pu32BootSelLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BOOT_SEL_LOCK_1(HI_VOID* arg)
{
    HI_U32 *pu32BootSelLock = (HI_U32*)arg;

    if (HI_NULL == pu32BootSelLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetBootSelLock_1(pu32BootSelLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BLOAD_DEC_EN(HI_VOID* arg)
{
    HI_U32 *pu32BloadDecEn = (HI_U32*)arg;

    if (HI_NULL == pu32BloadDecEn)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetBloadDecEn(pu32BloadDecEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BLOAD_DEC_EN_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32BloadDecEnLock = (HI_U32*)arg;

    if (HI_NULL == pu32BloadDecEnLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetBloadDecEnLock(pu32BloadDecEnLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_SELFBOOT(HI_VOID* arg)
{
    HI_U32 *pu32SelfBoot = (HI_U32*)arg;

    if (HI_NULL == pu32SelfBoot)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetSelfBoot(pu32SelfBoot);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_SELFBOOT_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32Lock = (HI_U32*)arg;

    if (HI_NULL == pu32Lock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetSelfbootLock(pu32Lock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_LOWPOWER_DISABLE(HI_VOID* arg)
{
    HI_U32 *pu32LowPowerDisable = (HI_U32*)arg;

    if (HI_NULL == pu32LowPowerDisable)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetLowPowerDisable(pu32LowPowerDisable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_LOWPOWER_DISABLE_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32Lock = (HI_U32*)arg;

    if (HI_NULL == pu32Lock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetLowPowerDisableLock(pu32Lock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_GETLADDERLOCK(HI_VOID* arg)
{
    HI_U32 *pu32Lock = (HI_U32*)arg;

    if (HI_NULL == pu32Lock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetDVBLadderLock(pu32Lock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_CSA3_GETLADDER(HI_VOID* arg)
{
    HI_UNF_ADVCA_KEYLADDER_LEV_E *pCSA3Ladder = (HI_UNF_ADVCA_KEYLADDER_LEV_E*)arg;

    if (HI_NULL == pCSA3Ladder)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_GetCSA3LadderLevel(pCSA3Ladder);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_CSA3_GETLADDERLOCK(HI_VOID* arg)
{
    HI_U32 *pu32Lock = (HI_U32*)arg;

    if (HI_NULL == pu32Lock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetCSA3LadderLock(pu32Lock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_R2R_GETLADDERLOCK(HI_VOID* arg)
{
    HI_U32 *pu32Lock = (HI_U32*)arg;

    if (HI_NULL == pu32Lock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetR2RLadderLock(pu32Lock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SP_GETLADDERLOCK(HI_VOID* arg)
{
    HI_U32 *pu32Lock = (HI_U32*)arg;

    if (HI_NULL == pu32Lock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetSPLadderLock(pu32Lock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_LINK_PRT_DISABLE_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32Lock = (HI_U32*)arg;

    if (HI_NULL == pu32Lock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetLinkProtectDisableLock(pu32Lock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_CSA2_HARDONLY_EN(HI_VOID* arg)
{
    HI_U32 *pu32Csa2HardonlyEn = (HI_U32*)arg;

    if (HI_NULL == pu32Csa2HardonlyEn)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetTSCsa2HardonlyEn(pu32Csa2HardonlyEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_CSA2_HARDONLY_EN_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32Lock = (HI_U32*)arg;

    if (HI_NULL == pu32Lock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetTSCsa2HardonlyEnLock(pu32Lock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_CSA3_HARDONLY_EN(HI_VOID* arg)
{
    HI_U32 *pu32Csa3HardonlyEn = (HI_U32*)arg;

    if (HI_NULL == pu32Csa3HardonlyEn)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetTSCSA3HardonlyEn(pu32Csa3HardonlyEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_CSA3_HARDONLY_EN_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32Csa3HardonlyEnLock = (HI_U32*)arg;

    if (HI_NULL == pu32Csa3HardonlyEnLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetTSCSA3HardonlyEnLock(pu32Csa3HardonlyEnLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_SP_HARDONLY_EN(HI_VOID* arg)
{
    HI_U32 *pu32SpHardonlyEn = (HI_U32*)arg;

    if (HI_NULL == pu32SpHardonlyEn)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetTSSPHardonlyEn(pu32SpHardonlyEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_SP_HARDONLY_EN_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32SPHardonlyEnLock = (HI_U32*)arg;

    if (HI_NULL == pu32SPHardonlyEnLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetTSSPHardonlyEnLock(pu32SPHardonlyEnLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TSKL_CSA2_DISABLE(HI_VOID* arg)
{
    HI_U32 *pCsa2Disable = (HI_U32*)arg;

    if (HI_NULL == pCsa2Disable)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetTSCWDeactive(pCsa2Disable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TSKL_CSA2_DISABLE_LOCK(HI_VOID* arg)
{
    HI_U32 *pCsa2DisableLock = (HI_U32*)arg;

    if (HI_NULL == pCsa2DisableLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetTSCWDeactiveLock(pCsa2DisableLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TSKL_CSA3_DISABLE(HI_VOID* arg)
{
    HI_U32 *pCsa3Disable = (HI_U32*)arg;

    if (HI_NULL == pCsa3Disable)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetTSCSA3Deactive(pCsa3Disable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TSKL_CSA3_DISABLE_LOCK(HI_VOID* arg)
{
    HI_U32 *pCsa3DisableLock = (HI_U32*)arg;

    if (HI_NULL == pCsa3DisableLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetTSCSA3DeactiveLock(pCsa3DisableLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TSKL_SP_DISABLE(HI_VOID* arg)
{
    HI_U32 *pu32SPDisable = (HI_U32*)arg;

    if (HI_NULL == pu32SPDisable)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetTSSPDeactive(pu32SPDisable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TSKL_SP_DISABLE_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32SPDisableLock = (HI_U32*)arg;

    if (HI_NULL == pu32SPDisableLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetTSSPDeactiveLock(pu32SPDisableLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TSKL_DES_DISABLE(HI_VOID* arg)
{
    HI_U32 *pTsklDesDisable = (HI_U32*)arg;

    if (HI_NULL == pTsklDesDisable)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetDesDisable(pTsklDesDisable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TSKL_DES_DISABLE_LOCK(HI_VOID* arg)
{
    HI_U32 *pTsklDesDisableLock = (HI_U32*)arg;

    if (HI_NULL == pTsklDesDisableLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetDesDisableLock(pTsklDesDisableLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_MCKL_DES_HARD_DISABLE(HI_VOID* arg)
{
    HI_U32 *pMcklDesHardOnlyEn = (HI_U32*)arg;

    if (HI_NULL == pMcklDesHardOnlyEn)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetDesHardDisable(pMcklDesHardOnlyEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_MCKL_DES_HARD_DISABLE_LOCK(HI_VOID* arg)
{
    HI_U32 *pMcklDesHardOnlyEnLock = (HI_U32*)arg;

    if (HI_NULL == pMcklDesHardOnlyEnLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetDesHardDisableLock(pMcklDesHardOnlyEnLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BLOAD_MODE_SEL(HI_VOID* arg)
{
    HI_U32 *pu32BloadModeSel = (HI_U32*)arg;

    if (HI_NULL == pu32BloadModeSel)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetBloadModeSel(pu32BloadModeSel);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BLOAD_MODE_SEL_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32BloadModeSelLock = (HI_U32*)arg;

    if (HI_NULL == pu32BloadModeSelLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetBloadModeSelLock(pu32BloadModeSelLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_DDR_SCRAMBLE_EN(HI_VOID* arg)
{
    HI_U32 *pDdrScrambleEn = (HI_U32*)arg;

    if (HI_NULL == pDdrScrambleEn)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetDDRScrambleEn(pDdrScrambleEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_DDR_SCRAMBLE_EN_LOCK(HI_VOID* arg)
{
    HI_U32 *pDdrScrambleEnLock = (HI_U32*)arg;

    if (HI_NULL == pDdrScrambleEnLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetDDRScrambleEnLock(pDdrScrambleEnLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_OTP_GLOBAL_LOCK_EN(HI_VOID* arg)
{
    HI_U32 *pOtpGlobalLockEn = (HI_U32*)arg;

    if (HI_NULL == pOtpGlobalLockEn)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetOtpGlobalLockEn(pOtpGlobalLockEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_OTP_GLOBAL_LOCK_EN_LOCK(HI_VOID* arg)
{
    HI_U32 *pOtpGlobalLockEnLock = (HI_U32*)arg;

    if (HI_NULL == pOtpGlobalLockEnLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetOtpGlobalLockEnLock(pOtpGlobalLockEnLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_SECURE_CHIP_FLAG(HI_VOID* arg)
{
    HI_U32 *pu32SecureChipFlag = (HI_U32*)arg;

    if (HI_NULL == pu32SecureChipFlag)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetSecureChipFlag(pu32SecureChipFlag);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_SECURE_CHIP_FLAG_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32Lock = (HI_U32*)arg;

    if (HI_NULL == pu32Lock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetSecureChipFlagLock(pu32Lock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_DCAS_KL_DISABLE(HI_VOID* arg)
{
    HI_U32 *pDCASKlDisable = (HI_U32*)arg;

    if (HI_NULL == pDCASKlDisable)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetDcasKLDisable(pDCASKlDisable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_DCAS_KL_DISABLE_LOCK(HI_VOID* arg)
{
    HI_U32 *pDCASKlDisableLock = (HI_U32*)arg;

    if (HI_NULL == pDCASKlDisableLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetDcasKLDisableLock(pDCASKlDisableLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TS_OUT_DISABLE(HI_VOID* arg)
{
    HI_U32 *pu32Disable = (HI_U32*)arg;

    if (HI_NULL == pu32Disable)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetTsOutDisable(pu32Disable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TS_OUT_DISABLE_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32Lock = (HI_U32*)arg;

    if (HI_NULL == pu32Lock )
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetTsOutDisableLock(pu32Lock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_LPC_DISABLE(HI_VOID* arg)
{
    HI_U32 *pu32LpcEn = (HI_U32*)arg;

    if (HI_NULL == pu32LpcEn)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetLpcEn(pu32LpcEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_LPC_DISABLE_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32Lock = (HI_U32*)arg;

    if (HI_NULL == pu32Lock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetLpcEnLock(pu32Lock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_LPC_MASTER_DISABLE(HI_VOID* arg)
{
    HI_U32 *pu32LpcMasterEn = (HI_U32*)arg;

    if (HI_NULL == pu32LpcMasterEn)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetLpcMasterEn(pu32LpcMasterEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_LPC_MASTER_DISABLE_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32Lock = (HI_U32*)arg;

    if (HI_NULL == pu32Lock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetLpcMasterEnLock(pu32Lock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BOOTSEL_CTRL(HI_VOID* arg)
{
    HI_U32 *pu32BootSel = (HI_U32*)arg;

    if (HI_NULL == pu32BootSel)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetBootSelCtrl(pu32BootSel);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BOOTSEL_CTRL_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32Lock = (HI_U32*)arg;

    if (HI_NULL == pu32Lock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetBootSelCtrlLock(pu32Lock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_RUNTIME_CHECK_EN(HI_VOID* arg)
{
    HI_U32 *pu32RuntimeCheckEn = (HI_U32 *)arg;

    if (HI_NULL == pu32RuntimeCheckEn)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetRuntimeCheckEn(pu32RuntimeCheckEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_RUNTIME_CHECK_EN_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32RuntimeCheckEnLock = (HI_U32 *)arg;

    if (HI_NULL == pu32RuntimeCheckEnLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetRuntimeCheckEnLock(pu32RuntimeCheckEnLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_WAKEUP_DDR_CHECK_EN(HI_VOID* arg)
{
    HI_U32 *pu32WakeupDdrCheckEn = (HI_U32 *)arg;

    if (HI_NULL == pu32WakeupDdrCheckEn)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetWakeupDDRCheckEn(pu32WakeupDdrCheckEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_WAKEUP_DDR_CHECK_EN_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32WakeipDdrCheckEnLock = (HI_U32 *)arg;

    if (HI_NULL == pu32WakeipDdrCheckEnLock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetWakeupDDRCheckEnLock(pu32WakeipDdrCheckEnLock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_VERSION_CHECK_EN(HI_VOID* arg)
{
    HI_U32 *pu32VersionIDCheckEn = (HI_U32 *)arg;

    if (HI_NULL == pu32VersionIDCheckEn)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetVersionIDCheckEn(pu32VersionIDCheckEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_VERSION_CHECK_EN_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32Lock = (HI_U32 *)arg;

    if (HI_NULL == pu32Lock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetVersionIDCheckEnLock(pu32Lock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BL_MSID_CHECK_EN(HI_VOID* arg)
{
    HI_U32 *pu32BlMSIDCheckEn = (HI_U32 *)arg;

    if (HI_NULL == pu32BlMSIDCheckEn)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetBlMSIDCheckEn(pu32BlMSIDCheckEn);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BL_MSID_CHECK_EN_LOCK(HI_VOID* arg)
{
    HI_U32 *pu32Lock = (HI_U32 *)arg;

    if (HI_NULL == pu32Lock)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetBlMSIDCheckEnLock(pu32Lock);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_JTAG_READ_DISABLE(HI_VOID* arg)
{
    HI_U32 *pu32Disable = (HI_U32*)arg;

    if (HI_NULL == pu32Disable)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetJtagReadDisable(pu32Disable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_JTAG_WRITE_DISABLE(HI_VOID* arg)
{
    HI_U32 *pu32Disable = (HI_U32*)arg;

    if (HI_NULL == pu32Disable)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetJtagWriteDisable(pu32Disable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_DEBUG_DISABLE(HI_VOID* arg)
{
    HI_U32 *pu32Disable = (HI_U32*)arg;

    if (HI_NULL == pu32Disable)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetDebugDisable(pu32Disable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_RIGHT_CTRL_EN(HI_VOID* arg)
{
    HI_U32 *pu32RightCtrl = (HI_U32*)arg;

    if (HI_NULL == pu32RightCtrl)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetRigthCtrlEn(pu32RightCtrl);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_LINK_PRT_DISABLE(HI_VOID* arg)
{
    HI_U32 *pu32LinkPrtDisable = (HI_U32*)arg;

    if (HI_NULL == pu32LinkPrtDisable)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetLinkProtectDisable(pu32LinkPrtDisable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_PROTECT(HI_VOID* arg)
{
    return HI_ERR_CA_NOT_SUPPORT;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_PROTECT(HI_VOID* arg)
{
    return HI_ERR_CA_NOT_SUPPORT;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BOOTSEL_CTRL(HI_VOID* arg)
{
    HI_U32 u32BootSel ;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    u32BootSel = *(HI_U32*)arg;
    return DRV_CA_OTP_V200_SetBootSelCtrl(u32BootSel);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_CHECK_MARKET_ID_SET(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 u32MarketIdSet;
    HI_BOOL *pbIsMarketIdSet = (HI_BOOL*)arg;

    if (HI_NULL == pbIsMarketIdSet)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    ret = DRV_CA_OTP_V200_GetMktIdLock(&u32MarketIdSet);
    if (ret)
    {
        ret = HI_FAILURE;
    }
    else
    {
        ret = HI_SUCCESS;
    }
    *pbIsMarketIdSet = (HI_BOOL)u32MarketIdSet;
    return ret;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_EXT1_SETRSAKEY(HI_VOID* arg)
{
    /*The RSA key should be converted to N and E*/
    HI_S32 ret = HI_FAILURE;
    HI_U8 au8KeyBuf[512] = {0};
    CA_KEY_S *pKey = (CA_KEY_S*)arg;

    if (HI_NULL == pKey)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    /*The first 256 Bytes are the N value of RSA key*/
    memset(au8KeyBuf, 0x0, 512);
    memcpy(au8KeyBuf, pKey->KeyBuf, 256);
    ret = DRV_CA_OTP_V200_SetRSAKeyN(au8KeyBuf);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("Set rsa key N failed!\n");
        return ret;
    }
    /*The last 16 Bytes are the E value of RSA key*/
    memset(au8KeyBuf, 0x0, 32);
    memcpy(au8KeyBuf, (pKey->KeyBuf + 496), 16);
    ret = DRV_CA_OTP_V200_SetRSAKeyE(au8KeyBuf);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("Set rsa key E failed!\n");
        return ret;
    }
#if defined (CHIP_TYPE_hi3716mv410) || defined (CHIP_TYPE_hi3716mv420) || defined(CHIP_TYPE_hi3798cv200)  || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv200_a)
    /*Set rsa key crc*/
    ret = DRV_CA_OTP_V200_SetRSACRC(pKey->KeyBuf);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("Set rsa key crc failed!\n");
    }
#endif
    return ret;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_EXT1_GETRSAKEY(HI_VOID* arg)
{
    /*The RSA key should be converted to N and E*/
    HI_S32 ret = HI_FAILURE;
    HI_U8 au8KeyBuf[512] = {0};
    CA_KEY_S *pKey = (CA_KEY_S*)arg;

    if (HI_NULL == pKey)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    /*The first 256 Bytes are the N value of RSA key*/
    memset(pKey->KeyBuf, 0x0, 512);
    ret = DRV_CA_OTP_V200_GetRSAKeyN(au8KeyBuf);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("Get rsa key N failed!\n");
        return ret;
    }
    memcpy(pKey->KeyBuf, au8KeyBuf, 256);

    /*The last 16 Bytes are the E value of RSA key*/
    memset(au8KeyBuf, 0x0, 512);
    ret = DRV_CA_OTP_V200_GetRSAKeyE(au8KeyBuf);//Only read 16 bytes data
    memcpy((pKey->KeyBuf + 496), au8KeyBuf, 16);
    return ret;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_DCAS_OPEN(HI_VOID* arg)
{
    HI_UNF_CIPHER_ALG_E enAlg ;

    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    enAlg = *(HI_UNF_CIPHER_ALG_E*)arg;
    return HAL_ADVCA_V300_DCASOpen(enAlg);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_DCAS_CLOSE(HI_VOID* arg)
{
    return HAL_ADVCA_V300_DCASClose();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_DCAS_PARAM_ID_SET(HI_VOID* arg)
{
    CA_DCAS_PARAM_S *pDCASParam = (CA_DCAS_PARAM_S *)arg;

    if (HI_NULL == pDCASParam)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_DecryptDCAS(pDCASParam->level, pDCASParam->pDin, 0, 0, pDCASParam->pDout, 0);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SWPK_KEY_LADDER_OPEN(HI_VOID* arg)
{
    return HAL_ADVCA_V300_SWPKKeyLadderOpen();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SWPK_KEY_LADDER_CLOSE(HI_VOID* arg)
{
    return HAL_ADVCA_V300_SWPKKeyLadderClose();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_LOCKSECRETKEY(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;

    ret = DRV_CA_OTP_V200_SetRootKeyLock();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("DRV_CA_OTP_V200_SetRootKeyLock failed, ret: 0x%x\n", ret);
    }
    ret = DRV_CA_OTP_V200_SetChipIdLock();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("DRV_CA_OTP_V200_SetChipIdLock failed, ret: 0x%x\n", ret);
    }
    ret = DRV_CA_OTP_V200_LockRSAKey();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("DRV_CA_OTP_V200_LockRSAKey failed, ret: 0x%x\n", ret);
    }
    return ret;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_CHIP_VERSION(HI_VOID* arg)
{
    HI_CHAR *pChipVersion = (HI_CHAR*)arg;
    HI_U32 u32Version = 0;
    HI_U8 *pu8VirAddr = HI_NULL;

    if (HI_NULL == pChipVersion)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    pu8VirAddr= (HI_U8*)ioremap_nocache(CA_V300_CA_VERSION,0x10);
    if(HI_NULL == pu8VirAddr)
    {
        HI_ERR_OTP("ioremap_nocache map error\n");
        return HI_FAILURE;
    }
    CA_readReg(pu8VirAddr, &u32Version);
    iounmap(pu8VirAddr);
    snprintf(pChipVersion, sizeof(HI_U32), "%x", (u32Version & 0xff));
    return 0;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_CSA3_EN(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetCsa3En();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_CSA3_EN(HI_VOID* arg)
{
    HI_U32 *pu32Csa3En = (HI_U32*)arg;

    if (HI_NULL == pu32Csa3En)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetCsa3En(pu32Csa3En);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_LINK_PRT_DISABLE(HI_VOID* arg)
{
    HI_U32 *pu32Disable = (HI_U32*)arg;

    if (HI_NULL == pu32Disable)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_SetLinkProtectDisable(*pu32Disable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BLOAD_ENC_EN(HI_VOID* arg)
{
    HI_U32 *pu32Disable = (HI_U32*)arg;

    if (HI_NULL == pu32Disable)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_SetBloadEncDisable(*pu32Disable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_CSA2_HARDONLY_EN(HI_VOID* arg)
{
    HI_U32 *pu32Enable = (HI_U32*)arg;

    if (HI_NULL == pu32Enable)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_SetTSCsa2HardonlyEn(*pu32Enable);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_EXT0_SETCWDEACTIVE(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetCSA2Deactive();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_EXT0_GETCWDEACTIVE(HI_VOID* arg)
{
    HI_U32 *pCsa2Deactive = (HI_U32*)arg;

    if (HI_NULL == pCsa2Deactive)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetCSA2Deactive(pCsa2Deactive);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_EXT0_SETR2RDEACTIVE(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetR2RDeactive();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_EXT0_GETR2RDEACTIVE(HI_VOID* arg)
{
    HI_U32 *pR2RDeactive = (HI_U32*)arg;

    if (HI_NULL == pR2RDeactive)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetR2RDeactive(pR2RDeactive);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_EXT0_SETCSA3DEACTIVE(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetCSA3Deactive();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_EXT0_GETCSA3DEACTIVE(HI_VOID* arg)
{
    HI_U32 *pR2RDeactive = (HI_U32*)arg;

    if (HI_NULL == pR2RDeactive)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetCSA3Deactive(pR2RDeactive);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_EXT0_SETSPDEACTIVE(HI_VOID* arg)
{
    return DRV_CA_OTP_V200_SetSPDeactive();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_EXT0_GETSPDEACTIVE(HI_VOID* arg)
{
    HI_U32 *pSPDeactive = (HI_U32*)arg;

    if (HI_NULL == pSPDeactive)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetSPDeactive(pSPDeactive);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_OTP_RESET(HI_VOID* arg)
{
    return HAL_ADVCA_V300_ResetOTP();
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_REVISION(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    CA_KEY_S *pKey = (CA_KEY_S*)arg;
    HI_U32 u32VendorId = 0;
    HI_CHAR *str = HI_NULL;

    ret = DRV_CA_OTP_V200_GetVendorId((CA_OTP_VENDOR_TYPE_E *)&u32VendorId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("get vendor type failed, ret: 0x%x\n", ret);
        return ret;
    }

    str = (CA_OTP_VENDOR_NAGRA == u32VendorId) ? NAGRA_REVISION : ADVCA_REVISION;

    if (HI_NULL == pKey)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    strncpy(pKey->KeyBuf, str, sizeof(str) < sizeof(pKey->KeyBuf) ? sizeof(str) : sizeof(pKey->KeyBuf) - 1);

    return 0;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SUPPER_ID(HI_VOID* arg)
{
    CA_CMD_SUPPER_ID_S *pstCmdParam = (CA_CMD_SUPPER_ID_S *)arg;

    if (HI_NULL == pstCmdParam)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_ADVCA_V300_Ioctl_Child(pstCmdParam);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_EXT1_OTPREAD(HI_VOID* arg)
{
    OTP_ENTRY_S *pOtpEntry = (OTP_ENTRY_S *)arg;

    if (HI_NULL == pOtpEntry)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    pOtpEntry->value = DRV_CA_OTP_V200_Read(pOtpEntry->addr);
    return 0;
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_EXT1_OTPWRITEBYTE(HI_VOID* arg)
{
    OTP_ENTRY_S *pOtpEntry = (OTP_ENTRY_S *)arg;

    if (HI_NULL == pOtpEntry)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_WriteByte(pOtpEntry->addr,pOtpEntry->value);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_OTP_FUSE(HI_VOID* arg)
{
    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_SetOtpFuse((CA_OTP_ATTR_S*)arg);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_GET_OTP_FUSE(HI_VOID* arg)
{
    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return DRV_CA_OTP_V200_GetOtpFuse((CA_OTP_ATTR_S*)arg);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_KEYLADDER_ATTR(HI_VOID* arg)
{
    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_SetKeyladderAttr((CA_KEYLADDER_ATTR_S*)arg);
}

static HI_S32 DRV_ADVCA_V300_Ioctl_CMD_CA_SET_CAVENDOR_OPT(HI_VOID* arg)
{
    if (HI_NULL == arg)
    {
        HI_ERR_CA("invalid arg\n");
        return HI_FAILURE;
    }
    return HAL_ADVCA_V300_SetCavendorOpt((CA_VENDOR_OPT_S*)arg);
}

static DRV_ADVCA_IOCTL_FUNC_MAP_S g_astIoctlFuncMap[] =
{
    {CMD_CA_SET_CHIPID                       , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_CHIPID},
    {CMD_CA_GET_CHIPID                       , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_CHIPID},
    {CMD_CA_SET_CHIPID_LOCK                  , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_CHIPID_LOCK},
    {CMD_CA_GET_CHIPID_LOCK                  , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_CHIPID_LOCK},
    {CMD_CA_SET_MARKETID                     , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_MARKETID},
    {CMD_CA_GET_MARKETID                     , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_MARKETID},
    {CMD_CA_SET_MKTID_LOCK                   , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_MKTID_LOCK},
    {CMD_CA_GET_MKTID_LOCK                   , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_MKTID_LOCK},
    {CMD_CA_SET_STBSN                        , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_STBSN},
    {CMD_CA_GET_STBSN                        , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_STBSN},
    {CMD_CA_SET_STBSN_LOCK                   , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_STBSN_LOCK},
    {CMD_CA_GET_STBSN_LOCK                   , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_STBSN_LOCK},
    {CMD_CA_SET_VERSIONID                    , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_VERSIONID},
    {CMD_CA_GET_VERSIONID                    , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_VERSIONID},
    {CMD_CA_SET_VERSION_ID_LOCK              , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_VERSION_ID_LOCK},
    {CMD_CA_GET_VERSION_ID_LOCK              , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_VERSION_ID_LOCK},
    {CMD_CA_LOCKHARDCWSEL                    , DRV_ADVCA_V300_Ioctl_CMD_CA_LOCKHARDCWSEL},
    {CMD_CA_STATHARDCWSEL                    , DRV_ADVCA_V300_Ioctl_CMD_CA_STATHARDCWSEL},
    {CMD_CA_LOCKBOOTDECEN                    , DRV_ADVCA_V300_Ioctl_CMD_CA_LOCKBOOTDECEN},
    {CMD_CA_LOCKR2RHARDKEY                   , DRV_ADVCA_V300_Ioctl_CMD_CA_LOCKR2RHARDKEY},
    {CMD_CA_STATR2RHARDKEY                   , DRV_ADVCA_V300_Ioctl_CMD_CA_STATR2RHARDKEY},
    {CMD_CA_DISABLELPT                       , DRV_ADVCA_V300_Ioctl_CMD_CA_DISABLELPT},
    {CMD_CA_DISABLESELFBOOT                  , DRV_ADVCA_V300_Ioctl_CMD_CA_DISABLESELFBOOT},
    {CMD_CA_STATTDESLOCK                     , DRV_ADVCA_V300_Ioctl_CMD_CA_STATTDESLOCK},
    {CMD_CA_DVB_CRYPT                        , DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_CRYPT},
    {CMD_CA_DVB_SETLADDER                    , DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_SETLADDER},
    {CMD_CA_DVB_GETLADDER                    , DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_GETLADDER},
    {CMD_CA_DVB_SETLADDERLOCK                , DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_SETLADDERLOCK},
    {CMD_CA_DVB_GETLADDERLOCK                , DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_GETLADDERLOCK},
    {CMD_CA_DVB_SETALG                       , DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_SETALG},
    {CMD_CA_DVB_GETALG                       , DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_GETALG},
    {CMD_CA_R2R_CRYPT                        , DRV_ADVCA_V300_Ioctl_CMD_CA_R2R_CRYPT},
    {CMD_CA_R2R_SETLADDER                    , DRV_ADVCA_V300_Ioctl_CMD_CA_R2R_SETLADDER},
    {CMD_CA_R2R_GETLADDER                    , DRV_ADVCA_V300_Ioctl_CMD_CA_R2R_GETLADDER},
    {CMD_CA_R2R_SETLADDERLOCK                , DRV_ADVCA_V300_Ioctl_CMD_CA_R2R_SETLADDERLOCK},
    {CMD_CA_R2R_GETLADDERLOCK                , DRV_ADVCA_V300_Ioctl_CMD_CA_R2R_GETLADDERLOCK},
    {CMD_CA_R2R_SETALG                       , DRV_ADVCA_V300_Ioctl_CMD_CA_R2R_SETALG},
    {CMD_CA_R2R_GETALG                       , DRV_ADVCA_V300_Ioctl_CMD_CA_R2R_GETALG},
    {CMD_CA_SP_CRYPT                         , DRV_ADVCA_V300_Ioctl_CMD_CA_SP_CRYPT},
    {CMD_CA_SP_SETLADDER                     , DRV_ADVCA_V300_Ioctl_CMD_CA_SP_SETLADDER},
    {CMD_CA_SP_GETLADDER                     , DRV_ADVCA_V300_Ioctl_CMD_CA_SP_GETLADDER},
    {CMD_CA_SP_SETLADDERLOCK                 , DRV_ADVCA_V300_Ioctl_CMD_CA_SP_SETLADDERLOCK},
    {CMD_CA_SP_GETLADDERLOCK                 , DRV_ADVCA_V300_Ioctl_CMD_CA_SP_GETLADDERLOCK},
    {CMD_CA_SP_SETALG                        , DRV_ADVCA_V300_Ioctl_CMD_CA_SP_SETALG},
    {CMD_CA_SP_GETALG                        , DRV_ADVCA_V300_Ioctl_CMD_CA_SP_GETALG},
    {CMD_CA_CSA3_CRYPT                       , DRV_ADVCA_V300_Ioctl_CMD_CA_CSA3_CRYPT},
    {CMD_CA_CSA3_SETLADDER                   , DRV_ADVCA_V300_Ioctl_CMD_CA_CSA3_SETLADDER},
    {CMD_CA_CSA3_GETLADDER                   , DRV_ADVCA_V300_Ioctl_CMD_CA_CSA3_GETLADDER},
    {CMD_CA_CSA3_SETLADDERLOCK               , DRV_ADVCA_V300_Ioctl_CMD_CA_CSA3_SETLADDERLOCK},
    {CMD_CA_CSA3_GETLADDERLOCK               , DRV_ADVCA_V300_Ioctl_CMD_CA_CSA3_GETLADDERLOCK},
    {CMD_CA_DVB_CSA3_SETALG                  , DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_CSA3_SETALG},
    {CMD_CA_DVB_CSA3_GETALG                  , DRV_ADVCA_V300_Ioctl_CMD_CA_DVB_CSA3_GETALG},
    {CMD_CA_SET_BOOTMODE                     , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BOOTMODE},
    {CMD_CA_GET_BOOTMODE                     , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BOOTMODE},
    {CMD_CA_SET_BOOT_SEL_LOCK_0              , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BOOT_SEL_LOCK_0},
    {CMD_CA_SET_BOOT_SEL_LOCK_1              , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BOOT_SEL_LOCK_1},
    {CMD_CA_GET_BOOT_SEL_LOCK_0              , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BOOT_SEL_LOCK_0},
    {CMD_CA_GET_BOOT_SEL_LOCK_1              , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BOOT_SEL_LOCK_1},
    {CMD_CA_SET_SCSACTIVE                    , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SCSACTIVE},
    {CMD_CA_GET_SCSACTIVE                    , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_SCSACTIVE},
    {CMD_CA_SET_JTAGPRTMODE                  , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_JTAGPRTMODE},
    {CMD_CA_GET_JTAGPRTMODE                  , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_JTAGPRTMODE},
    {CMD_CA_SET_PROTECT                      , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_PROTECT},
    {CMD_CA_GET_PROTECT                      , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_PROTECT},
    {CMD_CA_SWPK_CRYPT                       , DRV_ADVCA_V300_Ioctl_CMD_CA_SWPK_CRYPT},
    {CMD_CA_EXT1_OTPREAD                     , DRV_ADVCA_V300_Ioctl_CMD_CA_EXT1_OTPREAD},
    {CMD_CA_EXT1_OTPWRITEBYTE                , DRV_ADVCA_V300_Ioctl_CMD_CA_EXT1_OTPWRITEBYTE},
    {CMD_CA_SET_BOOTSEL_CTRL                 , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BOOTSEL_CTRL},
    {CMD_CA_GET_BOOTSEL_CTRL                 , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BOOTSEL_CTRL},
    {CMD_CA_SET_BOOTSEL_CTRL_LOCK            , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BOOTSEL_CTRL_LOCK},
    {CMD_CA_GET_BOOTSEL_CTRL_LOCK            , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BOOTSEL_CTRL_LOCK},
    {CMD_CA_SET_RSA_KEY_N                    , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_RSA_KEY_N},
    {CMD_CA_SET_RSA_KEY_E                    , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_RSA_KEY_E},
    {CMD_CA_GET_RSA_KEY_N                    , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_RSA_KEY_N},
    {CMD_CA_GET_RSA_KEY_E                    , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_RSA_KEY_E},
    {CMD_CA_SET_RSA_KEY_LOCK                 , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_RSA_KEY_LOCK},
    {CMD_CA_GET_RSA_KEY_LOCK                 , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_RSA_KEY_LOCK},
    {CMD_CA_SET_DVB_ROOT_KEY                 , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_DVB_ROOT_KEY},
    {CMD_CA_SET_DVB_CSA3_ROOT_KEY            , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_DVB_CSA3_ROOT_KEY},
    {CMD_CA_SET_R2R_ROOT_KEY                 , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_R2R_ROOT_KEY},
    {CMD_CA_SET_SP_ROOT_KEY                  , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SP_ROOT_KEY},
    {CMD_CA_SET_JTAG_KEY                     , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_JTAG_KEY},
    {CMD_CA_SET_SECRET_KEY_LOCK              , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SECRET_KEY_LOCK},
    {CMD_CA_GET_SECRET_KEY_LOCK              , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_SECRET_KEY_LOCK},
    {CMD_CA_SET_VENDOR_ID                    , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_VENDOR_ID},
    {CMD_CA_GET_VENDOR_ID                    , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_VENDOR_ID},
    {CMD_CA_SET_VENDOR_ID_LOCK               , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_VENDOR_ID_LOCK},
    {CMD_CA_GET_VENDOR_ID_LOCK               , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_VENDOR_ID_LOCK},
    {CMD_CA_SET_BLOAD_DEC_EN                 , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BLOAD_DEC_EN},
    {CMD_CA_GET_BLOAD_DEC_EN                 , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BLOAD_DEC_EN},
    {CMD_CA_SET_BLOAD_DEC_EN_LOCK            , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BLOAD_DEC_EN_LOCK},
    {CMD_CA_GET_BLOAD_DEC_EN_LOCK            , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BLOAD_DEC_EN_LOCK},
    {CMD_CA_SET_BLOAD_ENC_EN                 , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BLOAD_ENC_EN},
    {CMD_CA_LOCKSECRETKEY                    , DRV_ADVCA_V300_Ioctl_CMD_CA_LOCKSECRETKEY},
    {CMD_CA_SET_BLOAD_MODE_SEL               , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BLOAD_MODE_SEL},
    {CMD_CA_GET_BLOAD_MODE_SEL               , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BLOAD_MODE_SEL},
    {CMD_CA_SET_BLOAD_MODE_SEL_LOCK          , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BLOAD_MODE_SEL_LOCK},
    {CMD_CA_GET_BLOAD_MODE_SEL_LOCK          , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BLOAD_MODE_SEL_LOCK},
    {CMD_CA_SET_SELFBOOT                     , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SELFBOOT},
    {CMD_CA_GET_SELFBOOT                     , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_SELFBOOT},
    {CMD_CA_SET_SELFBOOT_LOCK                , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SELFBOOT_LOCK},
    {CMD_CA_GET_SELFBOOT_LOCK                , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_SELFBOOT_LOCK},
    {CMD_CA_SET_LOWPOWER_DISABLE             , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_LOWPOWER_DISABLE},
    {CMD_CA_GET_LOWPOWER_DISABLE             , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_LOWPOWER_DISABLE},
    {CMD_CA_SET_LOWPOWER_DISABLE_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_LOWPOWER_DISABLE_LOCK},
    {CMD_CA_GET_LOWPOWER_DISABLE_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_LOWPOWER_DISABLE_LOCK},
    {CMD_CA_SET_LINK_PRT_DISABLE             , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_LINK_PRT_DISABLE},
    {CMD_CA_GET_LINK_PRT_DISABLE             , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_LINK_PRT_DISABLE},
    {CMD_CA_SET_LINK_PRT_DISABLE_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_LINK_PRT_DISABLE_LOCK},
    {CMD_CA_GET_LINK_PRT_DISABLE_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_LINK_PRT_DISABLE_LOCK},
    {CMD_CA_SET_CSA2_HARDONLY_EN             , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_CSA2_HARDONLY_EN},
    {CMD_CA_GET_CSA2_HARDONLY_EN             , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_CSA2_HARDONLY_EN},
    {CMD_CA_SET_CSA2_HARDONLY_EN_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_CSA2_HARDONLY_EN_LOCK},
    {CMD_CA_GET_CSA2_HARDONLY_EN_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_CSA2_HARDONLY_EN_LOCK},
    {CMD_CA_SET_CSA3_HARDONLY_EN             , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_CSA3_HARDONLY_EN},
    {CMD_CA_GET_CSA3_HARDONLY_EN             , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_CSA3_HARDONLY_EN},
    {CMD_CA_SET_CSA3_HARDONLY_EN_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_CSA3_HARDONLY_EN_LOCK},
    {CMD_CA_GET_CSA3_HARDONLY_EN_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_CSA3_HARDONLY_EN_LOCK},
    {CMD_CA_SET_SP_HARDONLY_EN               , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SP_HARDONLY_EN},
    {CMD_CA_GET_SP_HARDONLY_EN               , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_SP_HARDONLY_EN},
    {CMD_CA_SET_SP_HARDONLY_EN_LOCK          , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SP_HARDONLY_EN_LOCK},
    {CMD_CA_GET_SP_HARDONLY_EN_LOCK          , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_SP_HARDONLY_EN_LOCK},
    {CMD_CA_SET_TSKL_CSA2_DISABLE            , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TSKL_CSA2_DISABLE},
    {CMD_CA_GET_TSKL_CSA2_DISABLE            , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TSKL_CSA2_DISABLE},
    {CMD_CA_SET_TSKL_CSA2_DISABLE_LOCK       , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TSKL_CSA2_DISABLE_LOCK},
    {CMD_CA_GET_TSKL_CSA2_DISABLE_LOCK       , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TSKL_CSA2_DISABLE_LOCK},
    {CMD_CA_SET_TSKL_CSA3_DISABLE            , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TSKL_CSA3_DISABLE},
    {CMD_CA_GET_TSKL_CSA3_DISABLE            , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TSKL_CSA3_DISABLE},
    {CMD_CA_SET_TSKL_CSA3_DISABLE_LOCK       , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TSKL_CSA3_DISABLE_LOCK},
    {CMD_CA_GET_TSKL_CSA3_DISABLE_LOCK       , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TSKL_CSA3_DISABLE_LOCK},
    {CMD_CA_SET_TSKL_SP_DISABLE              , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TSKL_SP_DISABLE},
    {CMD_CA_GET_TSKL_SP_DISABLE              , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TSKL_SP_DISABLE},
    {CMD_CA_SET_TSKL_SP_DISABLE_LOCK         , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TSKL_SP_DISABLE_LOCK},
    {CMD_CA_GET_TSKL_SP_DISABLE_LOCK         , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TSKL_SP_DISABLE_LOCK},
    {CMD_CA_SET_TSKL_DES_DISABLE             , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TSKL_DES_DISABLE},
    {CMD_CA_GET_TSKL_DES_DISABLE             , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TSKL_DES_DISABLE},
    {CMD_CA_SET_TSKL_DES_DISABLE_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TSKL_DES_DISABLE_LOCK},
    {CMD_CA_GET_TSKL_DES_DISABLE_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TSKL_DES_DISABLE_LOCK},
    {CMD_CA_SET_MCKL_DES_HARD_DISABLE        , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_MCKL_DES_HARD_DISABLE},
    {CMD_CA_GET_MCKL_DES_HARD_DISABLE        , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_MCKL_DES_HARD_DISABLE},
    {CMD_CA_SET_MCKL_DES_HARD_DISABLE_LOCK   , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_MCKL_DES_HARD_DISABLE_LOCK},
    {CMD_CA_GET_MCKL_DES_HARD_DISABLE_LOCK   , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_MCKL_DES_HARD_DISABLE_LOCK},
    {CMD_CA_SET_DDR_SCRAMBLE_EN              , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_DDR_SCRAMBLE_EN},
    {CMD_CA_GET_DDR_SCRAMBLE_EN              , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_DDR_SCRAMBLE_EN},
    {CMD_CA_SET_DDR_SCRAMBLE_EN_LOCK         , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_DDR_SCRAMBLE_EN_LOCK},
    {CMD_CA_GET_DDR_SCRAMBLE_EN_LOCK         , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_DDR_SCRAMBLE_EN_LOCK},
    {CMD_CA_SET_OTP_GLOBAL_LOCK_EN           , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_OTP_GLOBAL_LOCK_EN},
    {CMD_CA_GET_OTP_GLOBAL_LOCK_EN           , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_OTP_GLOBAL_LOCK_EN},
    {CMD_CA_SET_OTP_GLOBAL_LOCK_EN_LOCK      , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_OTP_GLOBAL_LOCK_EN_LOCK},
    {CMD_CA_GET_OTP_GLOBAL_LOCK_EN_LOCK      , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_OTP_GLOBAL_LOCK_EN_LOCK},
    {CMD_CA_SET_SECURE_CHIP_FLAG             , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SECURE_CHIP_FLAG},
    {CMD_CA_GET_SECURE_CHIP_FLAG             , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_SECURE_CHIP_FLAG},
    {CMD_CA_SET_SECURE_CHIP_FLAG_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_SECURE_CHIP_FLAG_LOCK},
    {CMD_CA_GET_SECURE_CHIP_FLAG_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_SECURE_CHIP_FLAG_LOCK},
    {CMD_CA_SET_DCAS_KL_DISABLE              , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_DCAS_KL_DISABLE},
    {CMD_CA_GET_DCAS_KL_DISABLE              , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_DCAS_KL_DISABLE},
    {CMD_CA_SET_DCAS_KL_DISABLE_LOCK         , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_DCAS_KL_DISABLE_LOCK},
    {CMD_CA_GET_DCAS_KL_DISABLE_LOCK         , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_DCAS_KL_DISABLE_LOCK},
    {CMD_CA_SET_TS_OUT_DISABLE               , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TS_OUT_DISABLE},
    {CMD_CA_GET_TS_OUT_DISABLE               , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TS_OUT_DISABLE},
    {CMD_CA_SET_TS_OUT_DISABLE_LOCK          , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_TS_OUT_DISABLE_LOCK},
    {CMD_CA_GET_TS_OUT_DISABLE_LOCK          , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_TS_OUT_DISABLE_LOCK},
    {CMD_CA_SET_LPC_DISABLE                  , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_LPC_DISABLE},
    {CMD_CA_GET_LPC_DISABLE                  , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_LPC_DISABLE},
    {CMD_CA_SET_LPC_DISABLE_LOCK             , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_LPC_DISABLE_LOCK},
    {CMD_CA_GET_LPC_DISABLE_LOCK             , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_LPC_DISABLE_LOCK},
    {CMD_CA_SET_LPC_MASTER_DISABLE           , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_LPC_MASTER_DISABLE},
    {CMD_CA_GET_LPC_MASTER_DISABLE           , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_LPC_MASTER_DISABLE},
    {CMD_CA_SET_LPC_MASTER_DISABLE_LOCK      , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_LPC_MASTER_DISABLE_LOCK},
    {CMD_CA_GET_LPC_MASTER_DISABLE_LOCK      , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_LPC_MASTER_DISABLE_LOCK},
    {CMD_CA_SET_RUNTIME_CHECK_EN             , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_RUNTIME_CHECK_EN},
    {CMD_CA_GET_RUNTIME_CHECK_EN             , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_RUNTIME_CHECK_EN},
    {CMD_CA_SET_RUNTIME_CHECK_EN_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_RUNTIME_CHECK_EN_LOCK},
    {CMD_CA_GET_RUNTIME_CHECK_EN_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_RUNTIME_CHECK_EN_LOCK},
    {CMD_CA_SET_WAKEUP_DDR_CHECK_EN          , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_WAKEUP_DDR_CHECK_EN},
    {CMD_CA_GET_WAKEUP_DDR_CHECK_EN          , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_WAKEUP_DDR_CHECK_EN},
    {CMD_CA_SET_WAKEUP_DDR_CHECK_EN_LOCK     , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_WAKEUP_DDR_CHECK_EN_LOCK},
    {CMD_CA_GET_WAKEUP_DDR_CHECK_EN_LOCK     , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_WAKEUP_DDR_CHECK_EN_LOCK},
    {CMD_CA_SET_VERSION_CHECK_EN             , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_VERSION_CHECK_EN},
    {CMD_CA_GET_VERSION_CHECK_EN             , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_VERSION_CHECK_EN},
    {CMD_CA_SET_VERSION_CHECK_EN_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_VERSION_CHECK_EN_LOCK},
    {CMD_CA_GET_VERSION_CHECK_EN_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_VERSION_CHECK_EN_LOCK},
    {CMD_CA_SET_BL_MSID_CHECK_EN             , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BL_MSID_CHECK_EN},
    {CMD_CA_GET_BL_MSID_CHECK_EN             , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BL_MSID_CHECK_EN},
    {CMD_CA_SET_BL_MSID_CHECK_EN_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_BL_MSID_CHECK_EN_LOCK},
    {CMD_CA_GET_BL_MSID_CHECK_EN_LOCK        , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_BL_MSID_CHECK_EN_LOCK},
    {CMD_CA_SET_JTAG_READ_DISABLE            , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_JTAG_READ_DISABLE},
    {CMD_CA_GET_JTAG_READ_DISABLE            , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_JTAG_READ_DISABLE},
    {CMD_CA_SET_JTAG_WRITE_DISABLE           , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_JTAG_WRITE_DISABLE},
    {CMD_CA_GET_JTAG_WRITE_DISABLE           , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_JTAG_WRITE_DISABLE},
    {CMD_CA_SET_DEBUG_DISABLE                , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_DEBUG_DISABLE},
    {CMD_CA_GET_DEBUG_DISABLE                , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_DEBUG_DISABLE},
    {CMD_CA_SET_RIGHT_CTRL_EN                , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_RIGHT_CTRL_EN},
    {CMD_CA_GET_RIGHT_CTRL_EN                , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_RIGHT_CTRL_EN},
    {CMD_CA_EXT0_SETCWDEACTIVE               , DRV_ADVCA_V300_Ioctl_CMD_CA_EXT0_SETCWDEACTIVE},
    {CMD_CA_EXT0_GETCWDEACTIVE               , DRV_ADVCA_V300_Ioctl_CMD_CA_EXT0_GETCWDEACTIVE},
    {CMD_CA_EXT0_SETR2RDEACTIVE              , DRV_ADVCA_V300_Ioctl_CMD_CA_EXT0_SETR2RDEACTIVE},
    {CMD_CA_EXT0_GETR2RDEACTIVE              , DRV_ADVCA_V300_Ioctl_CMD_CA_EXT0_GETR2RDEACTIVE},
    {CMD_CA_EXT0_SETCSA3DEACTIVE             , DRV_ADVCA_V300_Ioctl_CMD_CA_EXT0_SETCSA3DEACTIVE},
    {CMD_CA_EXT0_GETCSA3DEACTIVE             , DRV_ADVCA_V300_Ioctl_CMD_CA_EXT0_GETCSA3DEACTIVE},
    {CMD_CA_EXT0_SETSPDEACTIVE               , DRV_ADVCA_V300_Ioctl_CMD_CA_EXT0_SETSPDEACTIVE},
    {CMD_CA_EXT0_GETSPDEACTIVE               , DRV_ADVCA_V300_Ioctl_CMD_CA_EXT0_GETSPDEACTIVE},
    {CMD_CA_EXT1_SETRSAKEY                   , DRV_ADVCA_V300_Ioctl_CMD_CA_EXT1_SETRSAKEY},
    {CMD_CA_EXT1_GETRSAKEY                   , DRV_ADVCA_V300_Ioctl_CMD_CA_EXT1_GETRSAKEY},
    {CMD_CA_CHECK_MARKET_ID_SET              , DRV_ADVCA_V300_Ioctl_CMD_CA_CHECK_MARKET_ID_SET},
    {CMD_CA_DCAS_OPEN                        , DRV_ADVCA_V300_Ioctl_CMD_CA_DCAS_OPEN},
    {CMD_CA_DCAS_CLOSE                       , DRV_ADVCA_V300_Ioctl_CMD_CA_DCAS_CLOSE},
    {CMD_CA_DCAS_PARAM_ID_SET                , DRV_ADVCA_V300_Ioctl_CMD_CA_DCAS_PARAM_ID_SET},
    {CMD_CA_SWPK_KEY_LADDER_OPEN             , DRV_ADVCA_V300_Ioctl_CMD_CA_SWPK_KEY_LADDER_OPEN},
    {CMD_CA_SWPK_KEY_LADDER_CLOSE            , DRV_ADVCA_V300_Ioctl_CMD_CA_SWPK_KEY_LADDER_CLOSE},
    {CMD_CA_GET_CHIP_VERSION                 , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_CHIP_VERSION},
    {CMD_CA_SET_CSA3_EN                      , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_CSA3_EN},
    {CMD_CA_GET_CSA3_EN                      , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_CSA3_EN},
    {CMD_CA_OTP_RESET                        , DRV_ADVCA_V300_Ioctl_CMD_CA_OTP_RESET},
    {CMD_CA_GET_REVISION                     , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_REVISION},
    {CMD_CA_SP_SET_DSC_MODE                  , DRV_ADVCA_V300_Ioctl_CMD_CA_SP_SET_DSC_MODE},
    {CMD_CA_SP_GET_DSC_MODE                  , DRV_ADVCA_V300_Ioctl_CMD_CA_SP_GET_DSC_MODE},
    {CMD_CA_SUPPER_ID                        , DRV_ADVCA_V300_Ioctl_CMD_CA_SUPPER_ID},
    {CMD_CA_SET_OTP_FUSE                     , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_OTP_FUSE},
    {CMD_CA_GET_OTP_FUSE                     , DRV_ADVCA_V300_Ioctl_CMD_CA_GET_OTP_FUSE},
    {CMD_CA_SET_KEYLADDER_ATTR               , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_KEYLADDER_ATTR},
    {CMD_CA_SET_CAVENDOR_OPT                 , DRV_ADVCA_V300_Ioctl_CMD_CA_SET_CAVENDOR_OPT},
};

HI_S32 DRV_ADVCA_V300_Ioctl(HI_U32 cmd, HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    HI_S32 i = 0;
    HI_S32 u32Size = 0;

    ret = ca_down_interruptible(g_pDrvSema);
    if (HI_FAILURE == ret)
    {
        HI_ERR_CA("down_interruptible err, ret:0x%x\n");
        return HI_FAILURE;
    }

    u32Size = sizeof(g_astIoctlFuncMap)/sizeof(g_astIoctlFuncMap[0]);
    for (i=0; i<u32Size; i++)
    {
        if (cmd == g_astIoctlFuncMap[i].u32Cmd)
        {
            ret = g_astIoctlFuncMap[i].pfnIoctl(arg);
            if (ret != HI_SUCCESS)
            {
                HI_ERR_CA("cmd ID: 0x%x failed, ret: 0x%x\n", cmd, ret);
            }
            break;
        }
    }
    if (i >= u32Size)
    {
        HI_ERR_CA("not support cmd ID: 0x%x\n", cmd);
    }

    ca_up(g_pDrvSema);

    return ret;
}

int DRV_ADVCA_V300_Open(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Value = 0;

    s32Ret = ca_down_interruptible(g_pDrvSema);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_CA("%s:  down_interruptible err ! \n", __FUNCTION__);
        return HI_FAILURE;
    }

    s32Ret = ca_atomic_inc_return(&u32Value);
    if (s32Ret != HI_SUCCESS)
    {
        ca_up(g_pDrvSema);
        return HI_FAILURE;
    }

    ca_up(g_pDrvSema);

    return 0;
}

int DRV_ADVCA_V300_Release(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Value = 0;

    s32Ret = ca_down_interruptible(g_pDrvSema);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_CA("%s:  down_interruptible err ! \n", __FUNCTION__);
        return HI_FAILURE;
    }

    s32Ret = ca_atomic_dec_return(&u32Value);
    if (s32Ret != HI_SUCCESS)
    {
        ca_up(g_pDrvSema);
        return HI_FAILURE;
    }

    if (0 == u32Value)
    {
        HI_INFO_CA("%s:  ok ! \n", __FUNCTION__);
    }

    ca_up(g_pDrvSema);

    return 0;
}

HI_S32  DRV_ADVCA_V300_ModeInit_0(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;

    DRV_ADVCA_SystemSetClock();
    DRV_ADVCA_SystemSetReset();
    DRV_ADVCA_RegisterMap();

    g_pDrvSema = ca_create_mutex();
    if (HI_NULL == g_pDrvSema)
    {
        HI_ERR_CA("%s:  fail to create ca mutex! \n", __FUNCTION__);
        return HI_FAILURE;
    }

    ca_initMutex(g_pDrvSema);

    ret = HAL_ADVCA_V300_Open();
    if (ret != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

#if   (defined(CHIP_TYPE_hi3798cv200) && !defined(HI_TEE_SUPPORT)) \
   || (defined(CHIP_TYPE_hi3798mv200) && !defined(HI_TEE_SUPPORT)) \
   || (defined(CHIP_TYPE_hi3798mv300) && !defined(HI_TEE_SUPPORT)) \
   || (defined(CHIP_TYPE_hi3798mv200_a) && !defined(HI_TEE_SUPPORT))
    //Set keyladder to secure keyladder
    DRV_ADVCA_WriteReg(CA_V300_KL_SEC_EN, CA_V300_KL_EN_MASK);
#endif

    return ret;
}

HI_S32  DRV_ADVCA_V300_ModeExit_0(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;

    DRV_ADVCA_RegisterUnMap();

    return ret;
}

/*--------------------------------------------END-------------------------------------*/

