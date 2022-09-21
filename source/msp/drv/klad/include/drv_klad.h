/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __DRV_KLAD_H__
#define __DRV_KLAD_H__

#include "hi_common.h"
#include "hi_unf_klad.h"
#include "hi_drv_advca.h"
#include "hi_drv_dev.h"
#include "hi_drv_proc.h"
#include "hi_error_mpi.h"
#include "drv_klad_ioctl.h"
#include "hi_drv_klad.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define CA_NAME "HI_CA"
#define DRV_KLAD_MAX_DEMUX_ADDR_CNT  32
#define DRV_KLAD_MAX_CIPHER_ADDR_CNT 8

#define DRV_KLAD_CHECK_NULL_PTR(ptr) \
    do {\
        if (NULL == (ptr))\
        {\
            HI_FATAL_KLAD("KLAD('%s') is NULL.\n", # ptr); \
            return HI_ERR_KLAD_INVALID_PARA; \
        } \
    } while (0)

#define DRV_KLAD_CHECK_ALG(alg, high) \
    do {\
        if ((alg) >= (high)) \
        {\
            HI_ERR_KLAD("invalid algorithm: %d\n", (alg)); \
            return HI_ERR_KLAD_INVALID_PARA;\
        }\
    } while(0)

#define DRV_KLAD_CHECK_TARGET(target, high) \
    do {\
        if ((target) >= (high)) \
        {\
            HI_ERR_KLAD("invalid target: %d\n", (target)); \
            return HI_ERR_KLAD_INVALID_PARA;\
        }\
    } while(0)

#define DRV_KLAD_CHECK_TARGET_ADDR(addr, high) \
    do {\
        if ((addr) >= (high)) \
        {\
            HI_ERR_KLAD("invalid target addr: %d\n", (addr)); \
            return HI_ERR_KLAD_INVALID_PARA;\
        }\
    } while(0)

#define DRV_KLAD_CHECK_LEVEL(level) \
    do {\
        if (((level) <= 1) || ((level) >= (HI_UNF_KLAD_LEVEL_BUTT))) \
        {\
            HI_ERR_KLAD("invalid klad level: %d\n", (level)); \
            return HI_ERR_KLAD_INVALID_PARA;\
        }\
    } while(0)


extern struct mutex g_klad_mutex;
extern struct list_head ca_list;
extern struct list_head klad_session_list;

/** keyladder target */
typedef enum
{
    DRV_KLAD_TARGET_DEMUX          = 0x0, /**<demux*/
    DRV_KLAD_TARGET_MULTI_CIPHER   = 0x1, /**<multicipher*/
    DRV_KLAD_TARGET_PAYLOAD_CIPHER = 0x2,     /**<playload cipher*/
    DRV_KLAD_TARGET_BUTT
} DRV_KLAD_TARGET_E;

/*注意: 此枚举必须和hi_unf_xxx.h中HI_UNF_KLAD_XXX的高位保持一致*/
typedef enum
{
    CA_ID_BASIC        = 0x0, // basic
    CA_ID_NAGRA        = 0x1, // Nagra
    CA_ID_IRDETO       = 0x2, // Irdeto
    CA_ID_CONAX        = 0x3, // Conax
    CA_ID_VERIMATRIX   = 0x7, // Verimatrix
    CA_ID_DCAS         = 0xc, // Dcas
    CA_ID_COMMON_CA          = 0x3f,//com ca
    CA_ID_BUTT
} CA_TYPE_E;

typedef struct
{
    HI_U32 cmd;
    HI_S32 (*f_driver_cmd_process)(HI_VOID* arg);
} DRV_KLAD_IOCTL_S;

typedef HI_S32 (* KLAD_IOCTL)(HI_U32 cmd, HI_VOID *arg);
typedef HI_S32 (* KLAD_MODULE_OPS)(HI_VOID);

typedef struct
{
    CA_TYPE_E ca;
    struct list_head list;
    KLAD_IOCTL      ioctl;
} KLAD_DRV_ZONE;

typedef struct
{
    HI_HANDLE handle; /*key, session handle*/
    pid_t    owner;  /**/
    struct mutex lock;
    struct list_head list;

    HI_HANDLE target;  /*attach target*/
    HI_U32    klad_type;

    HI_BOOL attr_flag;
    DRV_KLAD_ATTR_S attr;

    HI_BOOL sessiong_key_flag[HI_UNF_KLAD_LEVEL_BUTT];
    DRV_KLAD_SESSION_KEY_S session_key[HI_UNF_KLAD_LEVEL_BUTT];

    HI_BOOL content_key_flag;
    DRV_KLAD_CONTENT_KEY_S content_key;

    HI_BOOL content_iv_flag;
    DRV_KLAD_CONTENT_IV_S content_iv;
    DRV_KLAD_DBG_S dbg;
} DRV_KLAD_SESSION;

HI_S32 DRV_KLAD_Init(HI_VOID);
HI_S32 DRV_KLAD_Exit(HI_VOID);
HI_S32 DRV_KLAD_Create(HI_VOID* arg);
HI_S32 DRV_KLAD_Destory(HI_VOID* arg);
HI_S32 DRV_KLAD_Release(struct file* filp);
HI_S32 DRV_KLAD_Attach(HI_VOID* arg);
HI_S32 DRV_KLAD_Detach(HI_VOID* arg);
HI_S32 DRV_KLAD_GetAttr(HI_VOID* arg);
HI_S32 DRV_KLAD_SetAttr(HI_VOID* arg);
HI_S32 DRV_KLAD_SetSessionKey(HI_VOID* arg);
HI_S32 DRV_KLAD_SetContentKey(HI_VOID* arg);
HI_S32 DRV_KLAD_GetDBG(HI_VOID* arg);
HI_S32 DRV_KLAD_GetSession(HI_HANDLE handle, DRV_KLAD_SESSION **session);
DRV_KLAD_TARGET_E DRV_KLAD_GetTarget(DRV_KLAD_SESSION *session);
HI_S32 DRV_KLAD_Register(KLAD_DRV_ZONE* zone);
HI_S32 DRV_KLAD_UnRegister(KLAD_DRV_ZONE* zone);
HI_VOID DRV_KLAD_Msleep(HI_U32 time);
HI_S32 DRV_KLAD_Ioctl(struct inode* inode, struct file* file, unsigned int cmd, void* arg);
HI_VOID DRV_KLAD_PrintSession(DRV_KLAD_SESSION *session);
HI_S32 DRV_KLAD_SetContentIV(HI_VOID * arg);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif  /* __DRV_KLAD_H__ */
