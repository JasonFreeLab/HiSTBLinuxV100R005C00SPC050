/***********************************************************************************
*              Copyright 2004 - 2015, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :  hi_tee_vdp.h
* Description:
*
* History:
* Version      Date         Author        DefectNum    Description
* main\1    20150909    NA                 NULL      Create this file.
***********************************************************************************/

#ifndef __TEE_VDP_EXT_H__
#define __TEE_VDP_EXT_H__

#include "hi_type.h"
#include "hi_tee_verimatrix.h"
#include "hi_tee_errcode.h"
#include "hi_tee_video_watermark.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define IOCTL_VDP_MAX_SIZE 0x1000

#define TEE_VDP_IOC_NONE         0U
#define TEE_VDP_IOC_W            1U
#define TEE_VDP_IOC_R            2U
#define TEE_VDP_IOC_RW           3U

#define TEE_VDP_IOC(dir,type,nr,size) (((dir) << 30)|((size) << 16)|((type) << 8)|((nr) << 0))

#define TEE_VDP_IO(type,nr)          TEE_VDP_IOC(TEE_VDP_IOC_NONE,(type),(nr), 0)
#define TEE_VDP_IOR(type,nr,size)    TEE_VDP_IOC(TEE_VDP_IOC_R,(type),(nr), sizeof(size))
#define TEE_VDP_IOW(type,nr,size)    TEE_VDP_IOC(TEE_VDP_IOC_W,(type),(nr), sizeof(size))
#define TEE_VDP_IOWR(type,nr,size)   TEE_VDP_IOC(TEE_VDP_IOC_RW,(type),(nr),sizeof(size))

#define TEE_VDP_IOC_DIR(nr)          (((nr) >> 30) & 0x03)
#define TEE_VDP_IOC_TYPE(nr)         (((nr) >> 8) & 0xFF)
#define TEE_VDP_IOC_NR(nr)           (((nr) >> 0) & 0xFF)
#define TEE_VDP_IOC_SIZE(nr)         (((nr) >> 16) & 0x3FFF)


typedef struct hiNextGuard_Param_S
{
    HI_TEE_VWM_NEXGUARD_PARAM_S  stNexguard;
    HI_HANDLE hServiceIndex;
}NextGuard_Param_S;

typedef enum hiIOC_VO_E
{
    TEE_IOC_NXG_RESET = 0,
    TEE_IOC_NXG_CREATE,
    TEE_IOC_NXG_DESTROY,
    TEE_IOC_NXG_SET,
    TEE_IOC_NXG_GET,
    TEE_IOC_NXG_INIT,
    TEE_IOC_NXG_DEINIT,

    TEE_IOC_VM_OPEN,
    TEE_IOC_VM_SEND,
    TEE_IOC_VM_GET,
    TEE_IOC_VM_CLOSED,
    TEE_IOC_VM_INIT,
    TEE_IOC_VM_DEINIT,
    TEE_IOC_BUTT
} IOC_WIN_E;

//#define  HI_TEE_VDP_CMD_NXG_RESET     TEE_VDP_IOR(HI_MODULE_ID_VO,  TEE_IOC_NXG_RESET,  )
#define  HI_TEE_VDP_CMD_NXG_CREATE      TEE_VDP_IOWR(HI_MODULE_ID_VO,  TEE_IOC_NXG_CREATE, HI_HANDLE)
#define  HI_TEE_VDP_CMD_NXG_DESTROY     TEE_VDP_IOW(HI_MODULE_ID_VO,  TEE_IOC_NXG_DESTROY,  HI_HANDLE)
#define  HI_TEE_VDP_CMD_NXG_SET         TEE_VDP_IOW(HI_MODULE_ID_VO,  TEE_IOC_NXG_SET,  NextGuard_Param_S)
#define  HI_TEE_VDP_CMD_NXG_GET         TEE_VDP_IOR(HI_MODULE_ID_VO,  TEE_IOC_NXG_GET,  NextGuard_Param_S)
#define  HI_TEE_VDP_CMD_NXG_INIT        TEE_VDP_IO(HI_MODULE_ID_VO,  TEE_IOC_NXG_INIT)
#define  HI_TEE_VDP_CMD_NXG_DEINIT      TEE_VDP_IO(HI_MODULE_ID_VO,  TEE_IOC_NXG_DEINIT)


#define  HI_TEE_VDP_CMD_VM_OPEN       TEE_VDP_IOW(HI_MODULE_ID_VO,  TEE_IOC_VM_OPEN,   HI_HANDLE)
#define  HI_TEE_VDP_CMD_VM_SEND       TEE_VDP_IOW(HI_MODULE_ID_VO,  TEE_IOC_VM_SEND,   HI_TEE_VDP_VMX_PARAM_S)
#define  HI_TEE_VDP_CMD_VM_GET        TEE_VDP_IOR(HI_MODULE_ID_VO,  TEE_IOC_VM_GET,    HI_TEE_VDP_VMX_PARAM_S)
#define  HI_TEE_VDP_CMD_VM_CLOSED     TEE_VDP_IOW(HI_MODULE_ID_VO,  TEE_IOC_VM_CLOSED, HI_HANDLE)
#define  HI_TEE_VDP_CMD_VM_INIT       TEE_VDP_IO(HI_MODULE_ID_VO,  TEE_IOC_VM_INIT)
#define  HI_TEE_VDP_CMD_VM_DEINIT     TEE_VDP_IO(HI_MODULE_ID_VO,  TEE_IOC_VM_DEINIT)

typedef enum hiTEE_VDP_TA_CA_TYPE_E
{
    HI_TEE_VDP_TA_FORMAL = 0,
    HI_TEE_VDP_TA_TESTMODE = 0xdeadbeef,
    HI_TEE_VDP_TA_BUTT
}HI_TEE_VDP_TA_CA_TYPE_E;

typedef struct hiTEE_VDP_VMX_PARA_S
{
    HI_TEE_VWM_VERIMATRIX_PARAM_S hwParameters;
    HI_U8  bServiceIdx;
    HI_U32 payload_symbols_addr;
    HI_TEE_VDP_TA_CA_TYPE_E eVdpTestMode;
}HI_TEE_VDP_VMX_PARAM_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
