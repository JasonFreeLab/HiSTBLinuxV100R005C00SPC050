#ifndef _TEE_DRV_DISPCTRL_IOCTL_H__
#define _TEE_DRV_DISPCTRL_IOCTL_H__

#include "hi_tee_dispctrl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cpluscplus */

enum DISPCTRL_DRV_IOCTL_FUNC_ID
{
    TEE_DRV_DISPCTRL_CREATE = 0X0,
    TEE_DRV_DISPCTRL_DESTORY,
    TEE_DRV_DISPCTRL_SETHDCPSTRATEGY,
    TEE_DRV_DISPCTRL_GETHDCPSTRATEGY,
    TEE_DRV_DISPCTRL_SETANALOGOUTSTRATEGY,
    TEE_DRV_DISPCTRL_SETMACROVISION,
    TEE_DRV_DISPCTRL_SETCGMS,
    TEE_DRV_DISPCTRL_QUERYDISPCTRL
};

typedef struct {
    HI_HANDLE hDispCtrl;
    HI_HANDLE *hDispCtrl_ptr;
    HI_U32    Linker;
    HI_TEE_DISPCTRL_LINKER_TYPE_E enType;
    const HI_VOID *pStreamHandle;
    const HI_TEE_DISPCTRL_HDCP_PARAMETER_S *pstHdcpPara;
    HI_TEE_DISPCTRL_HDCP_LEVEL_E *penHdcpLevel;
    const HI_TEE_DISPCTRL_ANALOGOUTPUT_PARAMETER_S *stPara;
    HI_TEE_DISPCTRL_MACROVISION_MODE_E enMode;
    const HI_VOID *pData;
    const HI_TEE_DISPCTRL_CGMS_CFG_S *pstCgmsCfg;
}HI_TEE_DISPCTRL_DRV_IOCTRL_BUF;



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cpluscplus */


#endif
