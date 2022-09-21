/******************************************************************************

          Copyright (C), 2001-2015, HiSilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : hi_loader_info_v2.c
 Version         : Initial draft
 Author          : Device Chipset STB Development Dept
 Created Date    : 2015-07-29
 Last Modified by:
 Description     :
 Function List   :
 Change History  :
 Version  Date        Author     DefectNum         Description
 ******************************************************************************/

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/
#include "stdio.h"
#include "loader_osal.h"
#include "loader_debug.h"
#include "loader_dbinfo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

HI_S32 HI_LOADER_GetParameter(HI_LOADER_PARAM_S* pstParameter)
{
    LDDB_LOADER_INFO_S stLoaderInfo;
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_NULL_PTR == pstParameter);

    LOADER_MemSet(&stLoaderInfo, 0x00, sizeof(stLoaderInfo));
    s32Ret = LDDB_GetLoaderInfo(&stLoaderInfo);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(LDDB_GetLoaderInfo, s32Ret);
        return s32Ret;
    }

    LDDB_UPDPARAM_CONVERT(pstParameter, &stLoaderInfo.stUPDParamData);

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 HI_LOADER_SetParameter(HI_LOADER_PARAM_S* pstParameter)
{
    LDDB_LOADER_INFO_S stLoaderInfo;
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_NULL_PTR == pstParameter);
    LOADER_CHECK_PARAM(HI_LOADER_UPGRADE_TYPE_BUTT <= pstParameter->enUpgradeType);
    LOADER_CHECK_PARAM(HI_LOADER_UPGRADE_MODE_BUTT <= pstParameter->enUpgradeMode);

    LOADER_MemSet(&stLoaderInfo, 0x00, sizeof(stLoaderInfo));
    stLoaderInfo.stTAGParamData.bNeedUpgrade  = HI_TRUE;
    stLoaderInfo.stTAGParamData.bForceUpgrade = HI_FALSE;
    stLoaderInfo.stTAGParamData.bUsbBurn      = HI_FALSE;

    stLoaderInfo.stPrivateParam.u32FailedCnt  = 0;
    stLoaderInfo.stPrivateParam.bTagDestroy   = HI_FALSE;

    LDDB_UPDPARAM_CONVERT(&stLoaderInfo.stUPDParamData, pstParameter);

    s32Ret = LDDB_SetLoaderInfo(&stLoaderInfo);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(LDDB_SetLoaderInfo, s32Ret);
        return s32Ret;
    }

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 HI_LOADER_GetSoftwareVersion(HI_U32* pu32SoftwareVersion)
{
    HI_S32 s32Ret = HI_FAILURE;
    LDDB_SOFTWARE_INFO_S stSoftwareInfo;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_NULL_PTR == pu32SoftwareVersion);

    LOADER_MemSet(&stSoftwareInfo, 0x00, sizeof(stSoftwareInfo));
    s32Ret = LDDB_GetSoftwareInfo(&stSoftwareInfo);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(LDDB_GetSoftwareInfo, s32Ret);
        return s32Ret;
    }

    *pu32SoftwareVersion = stSoftwareInfo.u32SoftwareVersion;

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 HI_LOADER_GetDeviceInfo(HI_LOADER_DEVICEINFO_S* pstDeviceInfo)
{
    HI_S32 s32Ret = HI_FAILURE;
    LDDB_DEVICE_INFO_S stDeviceInfo;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_NULL_PTR == pstDeviceInfo);

    LOADER_MemSet(&stDeviceInfo, 0x00, sizeof(stDeviceInfo));
    s32Ret = LDDB_GetDeviceInfo(&stDeviceInfo);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(LDDB_GetDeviceInfo, s32Ret);
        return s32Ret;
    }

    pstDeviceInfo->u32OUI         = stDeviceInfo.u32OUI;
    pstDeviceInfo->u32AreaCode    = stDeviceInfo.u32AreaCode;
    pstDeviceInfo->u32HWVersion   = stDeviceInfo.u32HardwareVersion;
    pstDeviceInfo->u32HWSerialNum = stDeviceInfo.u32SerialNum;

    LOADER_FuncExit();
    return HI_SUCCESS;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

