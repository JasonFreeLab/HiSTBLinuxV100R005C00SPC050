/******************************************************************************

  Copyright (C), 2015-2035, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name:	hi_ext_hal_ext.h
  Version: 	Initial Draft
  Author: 	Hisilicon multimedia software group
  Created: 	2015/09/08
  Description: 
  History: 	modify    
******************************************************************************/
#ifndef __HI_EXT_HAL_MCU_H__
#define __HI_EXT_HAL_MCU_H__


#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

typedef enum hiHAL_MCUHOST_EVENT_E
{    
    MCUHOST_SYSTEMCLOSE,
    MCUHOST_BUTT
}HAL_MCUHOST_EVENT_E;

typedef HI_S32(*PFN_MCUHOST_NotifyProc)(HAL_MCUHOST_EVENT_E eMCUHOSTEVENT);

/*********************************************************************
    Function:     HI_HAL_MCUHOST_Init
    Description:  
    Parameter:   
    Return:       HI_SUCCESS 成功
	             HI_FAILURE 打开设备失败
********************************************************************/
HI_S32 HI_HAL_MCUHOST_Init();

/*********************************************************************
    Function:     HI_HAL_MCUHOST_Deinit
    Description:  
    Parameter:   
    Return:       HI_SUCCESS 成功
	             HI_FAILURE 打开设备失败
********************************************************************/
HI_S32 HI_HAL_MCUHOST_Deinit();

/*********************************************************************
    Function:     HI_HAL_MCUHOST_RegisterNotifyProc
    Description:  
    Parameter:   
    Return:       HI_SUCCESS 成功
	             HI_FAILURE 打开设备失败
********************************************************************/
HI_S32 HI_HAL_MCUHOST_RegisterNotifyProc(PFN_MCUHOST_NotifyProc pfnNotifyProc);

/*********************************************************************
    Function:     HI_HAL_MCUHOST_RegOn_Control
    Description:  
    Parameter:   
    Return:       HI_SUCCESS 成功
	             HI_FAILURE 打开设备失败
********************************************************************/
HI_S32 HI_HAL_MCUHOST_RegOn_Control(HI_CHAR u8enable);

/*********************************************************************
    Function:     HI_HAL_MCUHOST_RegOn_Control
    Description:  
    Parameter:   
    Return:       HI_SUCCESS 成功
	             HI_FAILURE 打开设备失败
********************************************************************/
HI_S32 HI_HAL_MCUHOST_PowreOff_Request();

/*********************************************************************
    Function:     HI_HAL_MCUHOST_Set_ShutDown_Interval
    Description:  
    Parameter:   
    Return:       HI_SUCCESS 成功
	             HI_FAILURE 打开设备失败
********************************************************************/
HI_S32 HI_HAL_MCUHOST_Set_ShutDown_Interval(HI_U32 u32Interval);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_EXT_HAL_MCU_H__ */

