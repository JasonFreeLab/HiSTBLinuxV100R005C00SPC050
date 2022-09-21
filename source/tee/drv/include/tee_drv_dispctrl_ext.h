/******************************************************************************
 *
 * Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : tee_drv_disctrl_ext.h
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2016-11-2
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * ******************************************************************************/
#ifndef __TEE_DRV_DISPCTRL_EXT_H__
#define __TEE_DRV_DISPCTRL_EXT_H__

#include"hi_tee_dispctrl.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

typedef struct
{
    HI_U32  Width;
    HI_U32  Height;

}TEE_DRV_DISPCTRL_FRAME_INFO_S;

/**
\brief Open an DISPCTRL device instance.
\brief CNcomment:创建DISPCTRL设备实例，返回设备句柄。 CNend
\attention \n
N/A
\param N/A                                                                          CNcomment:无。 CNend
\retval ::HI_SUCCESS                                                                CNcomment:系统调用成功。 CNend
\retval ::HI_TEE_ERROR_DISPCTRL_NOT_SUPPORT.                                        CNcomment:分配句柄失败。 CNend
\see \n
N/A
*/
HI_S32 TEE_DRV_DISPCTRL_Create(HI_HANDLE * phDispCtrl);

/**
\brief destory a DISPCTRL device instance.
\brief CNcomment:销毁 DISPCTRL 设备实例 CNend
\attention \n
N/A
\param N/A                                                                          CNcomment:无。 CNend
\retval ::HI_SUCCESS.                                                               CNcomment:系统调用成功。 CNend
\retval ::HI_TEE_ERROR_DISPCTRL_INVALIDE_HANDLE  Handle Invalide.                   CNcomment:无效句柄。 CNend
\see \n
N/A
*/
HI_S32 TEE_DRV_DISPCTRL_Destory(const HI_HANDLE hDispCtrl);

/**
\brief Config DISPCTRL HDCP policy.
\brief CNcomment:配置 DISPCTRL digital output hdcp 策略。 CNend
\attention \n
N/A
\param N/A                                                                          CNcomment:无。 CNend
\retval ::HI_SUCCESS                            .                                   CNcomment:系统调用成功。 CNend
\retval ::HI_TEE_ERROR_DISPCTRL_INVALIDE_HANDLE.                                    CNcomment:无效句柄。 CNend
\retval ::HI_TEE_ERROR_DISPCTRL_INVALIDE_PARA                                       CNcomment:无效参数。 CNend
\see \n
N/A
*/
HI_S32 TEE_DRV_DISPCTRL_SetHDCPStrategy(const HI_HANDLE hDispCtrl, const HI_VOID *pStreamHandle, const HI_TEE_DISPCTRL_HDCP_PARAMETER_S *pstHdcpPara);

/**
\brief get HDCP policy.
\brief CNcomment:获取 DISPCTRL hdcp 策略。 CNend
\attention \n
N/A
\param N/A                                                                          CNcomment:无。 CNend
\retval ::HI_SUCCESS                            .                                   CNcomment:系统调用成功。 CNend
\see \n
N/A
*/
//HI_S32 TEE_DRV_DISPCTRL_GetHDCPStrategy(TEE_DISPCTRL_HDCP_LEVEL_E *penHdcpLevel);

/**
\brief get DISPCTRL dugital output format.
\brief CNcomment:获取 DISPCTRL 数字输出制式。 CNend
\attention \n
N/A
\param N/A                                                                          CNcomment:无。 CNend
\retval ::HI_SUCCESS                            .                                   CNcomment:系统调用成功。 CNend
\retval ::HI_TEE_ERROR_DISPCTRL_INVALIDE_PARA                                       CNcomment:参数无效。 CNend
\see \n
N/A
*/
HI_S32 TEE_DRV_DISPCTRL_GetDigitalOutputFormat(const HI_HANDLE VfmwHandle, const TEE_DRV_DISPCTRL_FRAME_INFO_S *pSrcFmt, TEE_DRV_DISPCTRL_FRAME_INFO_S *pOutFmt);

/**
\brief set analog output strategy.
\brief CNcomment:关闭 DispctrlHandle 设备实例。 CNend
\attention \n
N/A
\param [in] hDispCtrl: dispctrl instance handle/A                                   CNcomment:无。 CNend
\param [in] stPara:  analogoutput ctrl prar/A                                       CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.                                     CNcomment:系统调用成功。 CNend
\see \n
N/A
*/
HI_S32 TEE_DRV_DISPCTRL_SetAnalogOutStrategy(const HI_HANDLE hDispCtrl, const HI_TEE_DISPCTRL_ANALOGOUTPUT_PARAMETER_S *stPara);

/**
\brief set macrovision strategy.
\brief CNcomment:关闭 DispctrlHandle 设备实例。 CNend
\attention \n
N/A
\param [in] hDispCtrl:dispctrl instance handle /A                                   CNcomment:无。 CNend
\param [in] enMode: macrovision mode/A                                              CNcomment:无。 CNend
\param [in] pData:only use for TEE_DISPCTRL_MACROVISION_MODE_CUSTOM mode            CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.                                     CNcomment:系统调用成功。 CNend
\see \n
N/A
*/
HI_S32 TEE_DRV_DISPCTRL_SetMacrovision(const HI_HANDLE hDispCtrl, const HI_TEE_DISPCTRL_MACROVISION_MODE_E enMode, const HI_VOID *pData );

/**
\brief set cgms strategy.
\brief CNcomment:关闭 DispctrlHandle 设备实例。 CNend
\attention \n
N/A
\param [in] hDispCtrl:dispctrl instance handle /A                                   CNcomment:无。 CNend
\param [in] pstCgmsCfg:cgms prar /A                                                 CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.                                     CNcomment:系统调用成功。 CNend
\see \n
N/A
*/
HI_S32 TEE_DRV_DISPCTRL_SetCgms(const HI_HANDLE hDispCtrl, const HI_TEE_DISPCTRL_CGMS_CFG_S *pstCgmsCfg );

/**
\brief query dispctrl handle.
\brief CNcomment:查询 DispctrlHandle 设备实例。 CNend
\attention \n
N/A
\param [in] hLinker:Linker instance handle /A                                       CNcomment:无。 CNend
\param [out] phDispCtrl:dispctrl instance handle /A                                 CNcomment:无。 CNend
\param [out] phDispCtrl:dispctrl instance handle /A                                 CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.                                     CNcomment:系统调用成功。 CNend
\see \n
N/A
*/
HI_S32 TEE_DRV_DISPCTRL_QueryDispctrl(const HI_U32 Linker,  const HI_TEE_DISPCTRL_LINKER_TYPE_E enType, HI_HANDLE *phDispCtrl );

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif


