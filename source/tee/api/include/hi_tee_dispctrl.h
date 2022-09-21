/******************************************************************************

  Copyright (C), 2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_tee_dispctrl.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2016-11-4
  Description   :
  History       :
  1.Date        :
  Author        : l00370809
  Modification  :

*******************************************************************************/
/**
 * \file
 * \brief Describes the API about the Dispctrl.
          CNcomment:提供DISPCTRL API CNend
 */

#ifndef __HI_TEE_DISPCTRL_H__
#define __HI_TEE_DISPCTRL_H__

#include "hi_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

typedef enum
{
    HI_TEE_DISPCTRL_HDCP_NONE = 0,  /* No HDCP protection*/
    HI_TEE_DISPCTRL_HDCP_1X,        /* HDCP1.4 or 2.0*/
    HI_TEE_DISPCTRL_HDCP_2X,        /* HDCP2.2 */
    HI_TEE_DISPCTRL_HDCP_BUTT,
}HI_TEE_DISPCTRL_HDCP_LEVEL_E;

/*Define video resolution type*/
typedef enum
{
    HI_TEE_DISPCTRL_RES_SD = 0,     /*SD(480 or 576)*/
    HI_TEE_DISPCTRL_RES_HD,         /*HD (720)*/
    HI_TEE_DISPCTRL_RES_FHD,        /*FHD (1080)*/
    HI_TEE_DISPCTRL_RES_UHD,        /*UHD (4K)*/
    HI_TEE_DISPCTRL_RES_BUTT,
}HI_TEE_DISPCTRL_RES_E;

/* Define digital output action type */
typedef enum
{
    HI_TEE_DISPCTRL_DIGOUT_PROHIBITED = 0,          /* Digital output is not allowed*/
    HI_TEE_DISPCTRL_DIGOUT_SD,                      /* SD(480 or 576) is allowed*/
    HI_TEE_DISPCTRL_DIGOUT_HD,                      /* HD (720) is allowed*/
    HI_TEE_DISPCTRL_DIGOUT_FHD,                     /* FHD (1080) is allowed*/
    HI_TEE_DISPCTRL_DIGOUT_UHD,                     /* UHD (4K) is allowed*/
    HI_TEE_DISPCTRL_DIGOUT_UNRESTRICTED = 0xFF,     /* No restriction*/
}HI_TEE_DISPCTRL_DIGITAL_ACTION_E;

typedef struct {
    HI_TEE_DISPCTRL_HDCP_LEVEL_E enHdcpReq;
    HI_TEE_DISPCTRL_DIGITAL_ACTION_E *penDigOutAction;
    HI_U32 u32HdcpLevelMax;
    HI_U32 u32ResolutionMax;
}HI_TEE_DISPCTRL_HDCP_PARAMETER_S;

/* Define dispctrl para */
typedef struct {
    HI_BOOL   bMute;                             /*default vid mute*/
}HI_TEE_DISPCTRL_ANALOGOUTPUT_PARAMETER_S;


/** define the enum of Macrovision output type*/
/** CNcomment:显示输出Macrovision模式枚举定义*/
typedef enum
{
    HI_TEE_DISPCTRL_MACROVISION_MODE_TYPE0 = 0,  /**<copy protection off *//**<CNcomment:*/
    HI_TEE_DISPCTRL_MACROVISION_MODE_TYPE1,      /**<AGC Process on, Split Burst Off *//**<*/
    HI_TEE_DISPCTRL_MACROVISION_MODE_TYPE2,      /**<AGC Process On, 2 Line SplitBurst On  *//**< */
    HI_TEE_DISPCTRL_MACROVISION_MODE_TYPE3,      /**<AGC Process On, 4 Line SplitBurst On  *//**< */
    HI_TEE_DISPCTRL_MACROVISION_MODE_CUSTOM,     /**<not support  *//**<CNcomment: */
    HI_TEE_DISPCTRL_MACROVISION_MODE_BUTT
} HI_TEE_DISPCTRL_MACROVISION_MODE_E;

/* CGMS type select */
/*CNcomment:CGMS 类型选择*/
typedef enum
{
    HI_TEE_DISPCTRL_CGMS_TYPE_A = 0x00,          /* CGMS type  A*//*CNcomment:CGMS 类型A*/
    HI_TEE_DISPCTRL_CGMS_TYPE_B,                 /* CGMS type  B*//*CNcomment:CGMS 类型B*/
    HI_TEE_DISPCTRL_CGMS_TYPE_BUTT
}HI_TEE_DISPCTRL_CGMS_TYPE_E;

/* definition of CGMS mode */
typedef enum
{
   HI_TEE_DISPCTRL_CGMS_MODE_COPY_FREELY = 0x0,   /* copying is permitted without restriction */
   HI_TEE_DISPCTRL_CGMS_MODE_COPY_NO_MORE,        /* No more copies are allowed (one generation copy has been made) */
   HI_TEE_DISPCTRL_CGMS_MODE_COPY_ONCE,           /* One generation of copies may be made */
   HI_TEE_DISPCTRL_CGMS_MODE_COPY_NEVER,          /* No copying is permitted */
   HI_TEE_DISPCTRL_CGMS_MODE_BUTT
}HI_TEE_DISPCTRL_CGMS_MODE_E;

/** definition of CGMS configuration */
typedef struct
{
    HI_BOOL                      bEnable;         /** HI_TRUE:CGMS is enabled; HI_FALSE:CGMS is disabled */
    HI_TEE_DISPCTRL_CGMS_TYPE_E  enType;          /** type-A or type-B or None(BUTT) */
    HI_TEE_DISPCTRL_CGMS_MODE_E  enMode;          /** CGMS mode. */
}HI_TEE_DISPCTRL_CGMS_CFG_S;

typedef enum
{
   HI_TEE_DISPCTRL_LINKER_VDEC_ES_ADDR = 0x0,    /*Linker trpe is Vdec Es buffer addr */
   HI_TEE_DISPCTRL_LINKER_BUTT
}HI_TEE_DISPCTRL_LINKER_TYPE_E;

/******************************* API declaration *****************************/
/**
\brief Create an Dispctrl device instance.
\brief CNcomment:创建dispctrl 实例，返回实例句柄。 CNend
\attention \n
N/A
\param[out] phDispCtrl: Create handle/A                                             CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.                                     CNcomment:系统调用成功。 CNend
\retval ::HI_TEE_ERROR_DISPCTRL_NOT_SUPPORT                         .               CNcomment:分配句柄失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_DISPCTRL_Create(HI_HANDLE * phDispCtrl);

/**
\brief Destory an Dispctrl device instance.
\brief CNcomment:关闭 DispctrlHandle 设备实例。 CNend
\attention \n
N/A
\param [in] hDispCtrl: dispctrl instance handle/A                                   CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.                                     CNcomment:系统调用成功。 CNend
\retval ::HI_TEE_ERROR_DISPCTRL_INVALIDE_HANDLE.                                    CNcomment:无效句柄。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_DISPCTRL_Destroy(const HI_HANDLE hDispCtrl);

/**
\brief Config HDCP policy.
\brief CNcomment:配置 DispctrlHandle digital output hdcp 策略。 CNend
\attention \n
N/A
\param [in] hDispCtrl: dispctrl instance handle/A                                   CNcomment:无。 CNend
\param [in] *pStreamHandle: Stream Handle/A                                         CNcomment:无。 CNend
\param [in] enHdcpReq: hdcp level/A                                                 CNcomment:无。 CNend
\param [in] *penDigOutAction: hdcp policy table/A                                   CNcomment:无。 CNend
\param [in] u32HdcpLevelMax: max hdcp level/A                                       CNcomment:无。 CNend
\param [in] u32ResolutionMax: max streame resoulation/A                             CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.                                     CNcomment:系统调用成功。 CNend
\retval ::HI_TEE_ERROR_DISPCTRL_INVALIDE_HANDLE.                                    CNcomment:无效句柄。 CNend
\retval ::HI_TEE_ERROR_DISPCTRL_INVALIDE_PARA.                                      CNcomment:无效参数。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_DISPCTRL_SetHDCPStrategy(const HI_HANDLE hDispCtrl, const HI_VOID  *pStreamHandle, const HI_TEE_DISPCTRL_HDCP_PARAMETER_S *stHdcpPara);

/**
\brief get HDCP policy.
\brief CNcomment:获取 DISPCTRL hdcp 策略。 CNend
\attention \n
N/A
\param [out]:penHdcpLevel get current HDCP level /A                                 CNcomment:无。 CNend
\retval ::HI_SUCCESS                            .                                   CNcomment:系统调用成功。 CNend
\see \n
N/A
*/
//HI_S32 HI_TEE_DISPCTRL_GetHDCPStrategy(TEE_DISPCTRL_HDCP_LEVEL_E *penHdcpLevel);

/**
\brief set analog output strategy.
\brief CNcomment:设置模拟输出策略。 CNend
\attention \n
N/A
\param [in] hDispCtrl: dispctrl instance handle/A                                   CNcomment:无。 CNend
\param [in] stPara:  analogoutput ctrl prar/A                                       CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.                                     CNcomment:系统调用成功。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_DISPCTRL_SetAnalogOutStrategy(const HI_HANDLE hDispCtrl, const HI_TEE_DISPCTRL_ANALOGOUTPUT_PARAMETER_S *stPara);

/**
\brief set macrovision strategy.
\brief CNcomment:设置macrovision 策略。 CNend
\attention \n
N/A
\param [in] hDispCtrl:dispctrl instance handle /A                                   CNcomment:无。 CNend
\param [in] enMode: macrovision mode/A                                              CNcomment:无。 CNend
\param [in] pData:only use for TEE_DISPCTRL_MACROVISION_MODE_CUSTOM mode            CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.                                     CNcomment:系统调用成功。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_DISPCTRL_SetMacrovision(const HI_HANDLE hDispCtrl, const HI_TEE_DISPCTRL_MACROVISION_MODE_E enMode, const HI_VOID *pData );

/**
\brief set cgms strategy.
\brief CNcomment:设置cgms 策略。 CNend
\attention \n
N/A
\param [in] hDispCtrl:dispctrl instance handle /A                                   CNcomment:无。 CNend
\param [in] pstCgmsCfg:cgms prar /A                                                 CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.                                     CNcomment:系统调用成功。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_DISPCTRL_SetCgms(const HI_HANDLE hDispCtrl, const HI_TEE_DISPCTRL_CGMS_CFG_S *pstCgmsCfg );

/**
\brief query dispctrl handle.
\brief CNcomment:查询 DispctrlHandle 设备实例句柄。 CNend
\attention \n
N/A
\param [in] Linker:Linker para /A                                                   CNcomment:无。 CNend
\param [in] enType:Linker  type /A                                                  CNcomment:无。 CNend
\param [out] phDispCtrl:dispctrl instance handle /A                                 CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.                                     CNcomment:系统调用成功。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_DISPCTRL_QueryDispctrl(const HI_U32 Linker, const HI_TEE_DISPCTRL_LINKER_TYPE_E enType, HI_HANDLE *phDispCtrl );


/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif

