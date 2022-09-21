#ifndef __DRV_CGMS_H__
#define __DRV_CGMS_H__


#include "hi_type.h"

    
#define __TEE_WZ_XMU__

#ifdef __TEE_WZ_XMU__
#include "hi_tee_vdp.h"
#include "vdp_define.h"
#include "hi_tee_debug.h"
//#include "hi_tee_vdp_common.h"
#include "drv_vdp_com.h"
#include "tee_drv_vdp.h"
#include "hi_tee_errcode.h"

#define HI_ERR_DISP(fmt...)     HI_ERR_VDP(HI_MODULE_ID_VO, fmt)
#endif

#ifndef __TEE_WZ_XMU__
#ifndef __DISP_PLATFORM_BOOT__
#include "drv_disp_hal.h"
#include "drv_disp_isr.h"
#endif
#include "hi_drv_disp.h"
#endif

#define CgmsCheckNullPointer(ptr) \
    {                                \
        if (!ptr)                    \
        {                            \
            HI_ERR_DISP(HI_MODULE_ID_VO,"DISP ERROR! Input null pointer in %s!\n"); \
            return HI_TEE_ERR_INVALID_PARAM;  \
        }                             \
    }



#ifdef __TEE_WZ_XMU__
/* add tee cdms struct */

typedef enum hiDRV_DISP_CGMSA_MODE_E
{
   HI_DRV_DISP_CGMSA_COPY_FREELY  = 0,
   HI_DRV_DISP_CGMSA_COPY_NO_MORE = 0x01,
   HI_DRV_DISP_CGMSA_COPY_ONCE    = 0x02,
   HI_DRV_DISP_CGMSA_COPY_NEVER   = 0x03,

   HI_DRV_DISP_CGMSA_MODE_BUTT
}HI_DRV_DISP_CGMSA_MODE_E;

//CGMS-A

typedef enum hiDRV_DISP_CGMSA_TYPE_E
{
    HI_DRV_DISP_CGMSA_A = 0x00,
    HI_DRV_DISP_CGMSA_B,
    HI_DRV_DISP_CGMSA_TYPE_BUTT
}HI_DRV_DISP_CGMSA_TYPE_E;

typedef struct hiDRV_DISP_CGMSA_CFG_S
{
    HI_BOOL           bEnable;
    HI_DRV_DISP_CGMSA_TYPE_E  enType;
    HI_DRV_DISP_CGMSA_MODE_E  enMode;
}HI_DRV_DISP_CGMSA_CFG_S;

#endif

typedef struct hiDISP_CGMS_INFO_S
{
#ifndef __DISP_PLATFORM_BOOT__
	HI_BOOL bEnable;
	HI_DRV_DISPLAY_E enAttachedDisp;
    HI_DRV_DISP_CGMSA_TYPE_E  enType;
    HI_DRV_DISP_CGMSA_MODE_E  enMode;
	HI_DRV_DISP_FMT_E enCurFormat;
#endif
}DISP_CGMS_INFO_S;


typedef struct hiDISP_CGMS_STATE_S
{
#ifndef __DISP_PLATFORM_BOOT__
	HI_BOOL bEnable;
	HI_DRV_DISPLAY_E enAttachedDisp;
    HI_DRV_DISP_CGMSA_TYPE_E  enType;
    HI_DRV_DISP_CGMSA_MODE_E  enMode;
#endif
}DISP_CGMS_STATE_S;

typedef struct hiDISP_CGMS_FMT_CFG_s
{
    HI_DRV_DISP_FMT_E enFmt;
    HI_U32  au32CfgData[HI_DRV_DISP_CGMSA_MODE_BUTT];
} DISP_CGMS_FMT_CFG_s;



HI_S32 DRV_CGMS_Init(HI_DRV_DISPLAY_E enDisp, HI_DRV_DISP_FMT_E enFmt, DISP_CGMS_INFO_S* pstCgms);

HI_S32 DRV_CGMS_DeInit(DISP_CGMS_INFO_S *pstCgms);

HI_S32 DRV_CGMS_Set(DISP_CGMS_INFO_S *pstCgms,HI_DRV_DISP_FMT_E enFormat,HI_DRV_DISP_CGMSA_CFG_S stCgmsCfg) ;

HI_S32 DRV_CGMS_Get(DISP_CGMS_INFO_S *pstCgms,DISP_CGMS_STATE_S *pstCurState) ;

//HI_S32 HI_DRV_VDP_SetCgms(HI_DRV_DISP_CGMSA_CFG_S stCgmsa);


#endif
