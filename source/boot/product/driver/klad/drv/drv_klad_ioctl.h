/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad_ioctl.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __DRV_KLAD_IOCTL_H__
#define __DRV_KLAD_IOCTL_H__

#include "hi_type.h"
#include "hi_unf_klad.h"
#include "hi_error_mpi.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */

#define BOOT_ADVCA_IOC_NA        0U
#define BOOT_ADVCA_IOC_W         1U
#define BOOT_ADVCA_IOC_R         2U
#define BOOT_ADVCA_IOC_RW        3U

#define BOOT_ADVCA_IOC(dir,type,nr,size) (((dir) << 30)|((size) << 16)|((type) << 8)|((nr) << 0))

#define BOOT_ADVCA_IO(type,nr)            BOOT_ADVCA_IOC(BOOT_ADVCA_IOC_R,(type),(nr), 0)
#define BOOT_ADVCA_IOR(type,nr,size)      BOOT_ADVCA_IOC(BOOT_ADVCA_IOC_R,(type),(nr), sizeof(size))
#define BOOT_ADVCA_IOW(type,nr,size)      BOOT_ADVCA_IOC(BOOT_ADVCA_IOC_W,(type),(nr), sizeof(size))
#define BOOT_ADVCA_IOWR(type,nr,size)     BOOT_ADVCA_IOC(BOOT_ADVCA_IOC_RW,(type),(nr),sizeof(size))

#define HI_ID_KLAD 0x5D

HI_S32 BOOT_KLAD_Ioctl(HI_U32 cmd, HI_VOID *argp);



typedef struct
{
    HI_UNF_KLAD_ALG_TYPE_E alg;
    HI_UNF_KLAD_TARGET_ENGINE_E engine;
} DRV_KLAD_ATTR_S;

/**drv session key*/
typedef struct
{
    HI_UNF_KLAD_LEVEL_E level;
    HI_U8 key[HI_UNF_KLAD_MAX_KEY_LEN];
} DRV_KLAD_SESSION_KEY_S;

/**drv content key*/
typedef struct
{
    HI_BOOL odd;
    HI_U8 key[HI_UNF_KLAD_MAX_KEY_LEN];
} DRV_KLAD_CONTENT_KEY_S;

/**Encrypted key*/
typedef struct
{
    HI_U8 clear_key[HI_UNF_KLAD_MAX_KEY_LEN];
    HI_U8 enc_key[HI_UNF_KLAD_MAX_KEY_LEN];
} DRV_KLAD_ENC_CLEAR_KEY_S;

typedef struct hiDRV_KLAD_DBG_S
{
    HI_U32 session_key_crc[HI_UNF_KLAD_LEVEL_BUTT];
    HI_U32 content_key_crc;
    HI_U32 check_err;
    HI_U32 klad_state;
} DRV_KLAD_DBG_S;

/**********************************************/
typedef struct hiKLAD_CTL_HANDLE_S
{
    HI_U32 klad;
    HI_HANDLE create_handle;  /*handle created by driver*/
} KLAD_CTL_HANDLE_S;

typedef struct hiKLAD_CTL_TARGET_S
{
    HI_HANDLE handle;
    HI_HANDLE target;
} KLAD_CTL_TARGET_S;

typedef struct hiKLAD_CTL_ATTR_S
{
    HI_HANDLE handle;
    DRV_KLAD_ATTR_S attr;
} KLAD_CTL_ATTR_S;

typedef struct hiKLAD_CTL_SESSION_KEY_S
{
    HI_HANDLE handle;
    DRV_KLAD_SESSION_KEY_S session_key;
} KLAD_CTL_SESSION_KEY_S;

typedef struct hiKLAD_CTL_CONTENT_KEY_S
{
    HI_HANDLE handle;
    DRV_KLAD_CONTENT_KEY_S content_key;
} KLAD_CTL_CONTENT_KEY_S;

typedef struct hiKLAD_CTL_ENC_KEY_S
{
    HI_HANDLE handle;
    DRV_KLAD_ENC_CLEAR_KEY_S key;
} KLAD_CTL_ENC_CLEAR_KEY_S;

typedef struct hiKLAD_CTL_KLAD_DBG_S
{
    HI_HANDLE handle;
    DRV_KLAD_DBG_S dbg;
} KLAD_CTL_DBG_S;

typedef struct
{
    HI_HANDLE handle;
    HI_U8 kwmcwc[16];
} KLAD_CTL_KWMCWC_S;



#define CMD_KLAD_CREATE                     BOOT_ADVCA_IOWR(HI_ID_KLAD, 0x1, KLAD_CTL_HANDLE_S)
#define CMD_KLAD_DESTORY                    BOOT_ADVCA_IOW (HI_ID_KLAD, 0x2, HI_HANDLE)
#define CMD_KLAD_ATTACH                     BOOT_ADVCA_IOWR(HI_ID_KLAD, 0x3, KLAD_CTL_TARGET_S)
#define CMD_KLAD_DETACH                     BOOT_ADVCA_IOWR(HI_ID_KLAD, 0x4, KLAD_CTL_TARGET_S)
#define CMD_KLAD_GET_ATTR                   BOOT_ADVCA_IOWR(HI_ID_KLAD, 0x5, KLAD_CTL_ATTR_S)
#define CMD_KLAD_SET_ATTR                   BOOT_ADVCA_IOW (HI_ID_KLAD, 0x6, KLAD_CTL_ATTR_S)
#define CMD_KLAD_GET_DEFAULT_ATTR           BOOT_ADVCA_IOWR(HI_ID_KLAD, 0x7, KLAD_CTL_ATTR_S)
#define CMD_KLAD_SET_SESSION_KEY            BOOT_ADVCA_IOW (HI_ID_KLAD, 0x8, KLAD_CTL_SESSION_KEY_S)
#define CMD_KLAD_SET_CONTENT_KEY            BOOT_ADVCA_IOW (HI_ID_KLAD, 0x9, KLAD_CTL_CONTENT_KEY_S)
#define CMD_KLAD_GEN_ENC_KEY                BOOT_ADVCA_IOWR(HI_ID_KLAD, 0xa, KLAD_CTL_ENC_CLEAR_KEY_S)
#define CMD_KLAD_GET_DBG                    BOOT_ADVCA_IOWR(HI_ID_KLAD, 0xb, KLAD_CTL_DBG_S)
#define CMD_KLAD_BOOT2CIPHER                BOOT_ADVCA_IOW (HI_ID_KLAD, 0xc, HI_HANDLE)
#define CMD_KLAD_SET_MISC_KWMCWC            BOOT_ADVCA_IOW (HI_ID_KLAD, 0xd, KLAD_CTL_KWMCWC_S)
#define CMD_KLAD_SET_SP_KWMCWC              BOOT_ADVCA_IOW (HI_ID_KLAD, 0xe, KLAD_CTL_KWMCWC_S)
#define CMD_KLAD_SET_COM_CA_CONTENT_KEY     BOOT_ADVCA_IOW (HI_ID_KLAD, 0xd, KLAD_CTL_CONTENT_KEY_S)

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __DRV_KLAD_IOCTL_H__ */
