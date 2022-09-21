#ifndef _TEE_DRV_HDMI_IOCTL_H__
#define _TEE_DRV_HDMI_IOCTL_H__

#include "hi_tee_hdmi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cpluscplus */


enum HDMI_DRV_IOCTL_FUNC_ID
{
	HI_DRV_HDMI_SETSRM = 0x0,
	HI_DRV_HDMI_SETHDCPSTRATEGY,
	HI_DRV_HDMI_GETHDCPSTRATEGY,
	HI_DRV_HDMI_GETHDCPSTATUS,
	HI_DRV_HDMI_SETHDCPMUTE,
	HI_DRV_HDMI_HDCP22_INIT,
	HI_DRV_HDMI_TEEPROC,
	HI_DRV_HDMI_SETHDCPCAPS,
	HI_DRV_HDMI_IOCTRL_ID,
	HI_DRV_HDMI_GETHDCPCAPS,
	HI_DRV_HDMI_INIT,
	HI_DRV_HDMI_DEINIT,
	HI_DRV_HDMI_START,
	HI_DRV_HDMI_STOP,
	HI_DRV_HDMI_GETHDMISTATUS,
};

typedef struct
{
    HI_TEE_HDMI_ID_E            enHdmiId;
    HI_TEE_HDMI_SRM_S           *pstSrm;
    HI_TEE_HDMI_HDCP_LEVLEL_E   enHdcpLevel;
    HI_TEE_HDMI_HDCP_LEVLEL_E   *penHdcpLevel;
    HI_TEE_HDMI_HDCP_STATUS_E   *penHdcpStatus;
    HI_TEE_HDMI_HDCP_CAPS_S     *pstHdcpCaps;
    HI_TEE_HDMI_STATUS_S        *pstHdmiStatus;
    HI_BOOL                     bMute;
    HI_VOID                     *pvData;
    HI_U32                      u32Size;
} HI_TEE_HDMI_DRV_IOCTRL_BUF;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cpluscplus */


#endif
