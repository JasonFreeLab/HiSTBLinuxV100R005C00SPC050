#ifndef __TEE_DRV_HDMI_COMMON_H__
#define __TEE_DRV_HDMI_COMMON_H__

#include "hi_type.h"
#include "hi_tee_debug.h"
#include "sre_ticktimer_functions.h"
#include "tee_drv_hdmi.h"
#include "tee_drv_hdmi_hal.h"
#include "tee_drv_hdmi_srm.h"
#include "tee_os_hal.h"
#include "hi_tee_debug.h"
#include "hi_tee_errcode.h"
#include "hi_tee_module_id.h"
#include "hi_tee_debug.h"






/******************************************************************************/
/* HDMI Version                                                               */
/******************************************************************************/
#define HDMI_VER_MAJOR    1
#define HDMI_VER_MINOR    0
#define HDMI_VER_REVISE   0
#define HDMI_VER_DATE     20171019
#define HDMI_VER_TIMES    0

#define MAKE_VER_BIT(x) # x
#define MAKE_MACRO2STR(exp) MAKE_VER_BIT(exp)
#define MAKE_VERSION \
    MAKE_MACRO2STR(HDMI_VER_MAJOR) "."  \
    MAKE_MACRO2STR(HDMI_VER_MINOR) "."  \
    MAKE_MACRO2STR(HDMI_VER_REVISE) "." \
    MAKE_MACRO2STR(HDMI_VER_DATE) "."   \
    MAKE_MACRO2STR(HDMI_VER_TIMES)

#define CHECK_POINTER(func,p) \
do { \
    if(p == HI_NULL) \
    { \
        HI_LOG_PrintFuncErr(func,HI_TEE_ERR_INVALID_PARAM);\
        return HI_FAILURE; \
    } \
}while(0)

#define mSleep(msec)    tee_hal_msleep((msec))
#define Sleep(sec)      tee_hal_msleep((sec)*1000);


#define HDMI_TEE_PROC(fmt...)   HI_TEE_INFO_PRINT(HI_MODULE_ID_HDMI,fmt)

#ifndef HDMI_TEE_INFO

#define HDMI_TEE_FATA(fmt...)    HI_TEE_FATAL_PRINT(HI_MODULE_ID_HDMI,fmt)
#define HDMI_TEE_ERR(fmt...)     HI_TEE_ERR_PRINT(HI_MODULE_ID_HDMI,fmt)
#define HDMI_TEE_WARN(fmt...)    HI_TEE_WARN_PRINT(HI_MODULE_ID_HDMI,fmt)
#define HDMI_TEE_INFO(fmt...)    HI_TEE_INFO_PRINT(HI_MODULE_ID_HDMI,fmt)
#define HDMI_TEE_DBG(fmt...)     HI_TEE_DBG_PRINT(HI_MODULE_ID_HDMI,fmt)

#endif


/* enhance key operation security */
#define HDMI_KEY_SUCC   0xAC145884
#define HDMI_KEY_FAIL   0xF2788541

#define HDMI_KEY_TRUE   0xAC145887
#define HDMI_KEY_FALSE  0xF278854A

#define HDMI_KEY_LOOP   0x027CC54A

#define HDMI_KEY_METHOD 0x55

#define HDMI_SEC_MODE_ADD(x)    do{x += 2*HDMI_KEY_METHOD; }while(0)
#define HDMI_SEC_MODE_DEL(x)    do{x -= HDMI_KEY_METHOD + HDMI_KEY_METHOD; }while(0)

#define MAX_HDMI_TEE_DATA_SIZE              1024
#define MAX_SRM_SIZE_MAX_HEAD_FORMAT        5116




typedef struct
{
    HI_BOOL             bTimerCreate;
    HI_BOOL             bTimerIsRunning;
    timer_event*        timer_event;
}HI_DRV_HDMI_TIMER_INFO_S;

typedef enum hiDRV_HDMI_HDCP_VERSION_E
{
    HI_DRV_HDMI_HDCP_VER_NONE = 0,  /** no hdcp version */
    HI_DRV_HDMI_HDCP_14,        /** use hdcp1.4 version */
    HI_DRV_HDMI_HDCP_22,        /** use hdcp2.2 version */
    HI_DRV_HDMI_HDCP_VER_BUTT
} HI_DRV_HDMI_HDCP_VERSION_E;

typedef struct
{
    HDMI_SRM_CTX_S                  stSrmCtx;
    HDMI_HDCP_DEVID_INFO_S          stDevIdInfo;
}HI_DRV_HDMI_SRM_INFO_S;

typedef enum
{
    HI_DRV_HDMI_TEE_OK = 0,             /** TEE status OK */
    HI_DRV_HDMI_TEE_STOP_HDCP,          /** TEE stop HDCP */
    HI_DRV_HDMI_TEE_BUTT
} HI_DRV_HDMI_TEE_STATUS_E;

typedef struct
{
    HI_U32                          u32HdmiDevId;
    HI_BOOL                         enHdcpWasOn;
    HI_DRV_HDMI_HDCP_STATUS_E       enHdcpStatus;
    HI_DRV_HDMI_HDCP_VERSION_E      enHdcpVersion;
    HI_DRV_HDMI_HDCP_LEVEL_E        enHdcpLevel;
    HI_DRV_HDMI_HDCP_STREAM_TYPE_E  enHdcpStreamType;
    HI_DRV_HDMI_HADRWARE_STATUS_S   stHardwareStatus;
    HI_BOOL                         bHdcp22ProLoad;
    HI_BOOL                         bHdcp14Succ;
    HI_DRV_HDMI_TIMER_INFO_S        stTimerInfo;
    HI_DRV_HDMI_HDCP_CAPS_S         stHdcpCaps;
    HI_DRV_HDMI_SRM_INFO_S          stSrmInfo;
    HDMI_HDCP_MUTE_STATUS_S         stMuteStatus;
    TEE_HDMI_HAL_S                  stTeeHdmiHal;
    HI_DRV_HDMI_TEE_STATUS_E        enTeeStatus;
    HI_U8                           au8CmdData[MAX_HDMI_TEE_DATA_SIZE];
    HI_U8                           au8SrmData[MAX_SRM_SIZE_MAX_HEAD_FORMAT];

}TEE_HDMI_DEVICE_S;



#define HDMI_ACCESS_CHECK(func,addr, size)  if(!tee_hal_access_check(addr, size)){\
                    HI_LOG_PrintFuncErr(func,HI_TEE_ERR_UNSUPPORTED);\
                    return TEE_ERROR_ACCESS_DENIED;\
                    }

#define HDMI_ACCESS_READ_RIGHT_CHECK(func,addr, size)  if(!tee_hal_read_right_check(addr, size)){\
                    HI_LOG_PrintFuncErr(func,HI_TEE_ERR_UNSUPPORTED);\
                    return TEE_ERROR_ACCESS_DENIED;\
                    }

#define HDMI_ACCESS_WRITE_RIGHT_CHECK(func,addr, size)  if(!tee_hal_write_right_check(addr, size)){\
                    HI_LOG_PrintFuncErr(func,HI_TEE_ERR_UNSUPPORTED);\
                    return TEE_ERROR_ACCESS_DENIED;\
                    }


#endif


