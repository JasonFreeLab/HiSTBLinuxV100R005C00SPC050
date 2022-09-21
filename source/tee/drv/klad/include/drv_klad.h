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

#include "hi_tee_keyladder.h"
#include "hi_tee_errcode.h"

#include "hi_list.h"
#include "tee_drv_klad_ioctl.h"
#include "tee_os_hal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#ifdef CFG_HI_ADVCA_DCAS_SUPPORT
#define TEE_KLAD_CMD_INVALID(cmd) \
    ((cmd != CMD_KLAD_CREATE) \
     && (cmd != CMD_KLAD_DESTORY) \
     && (cmd != CMD_KLAD_ATTACH) \
     && (cmd != CMD_KLAD_DETACH) \
     && (cmd != CMD_KLAD_GET_ATTR) \
     && (cmd != CMD_KLAD_SET_ATTR) \
     && (cmd != CMD_KLAD_SET_SESSION_KEY) \
     && (cmd != CMD_KLAD_SET_CONTENT_KEY) \
     && (cmd != CMD_KLAD_GENERATE_ENCKEY) \
     && (cmd != CMD_KLAD_BOOT2CIPHER) \
     && (cmd != CMD_KLAD_SET_MISC_KWMCWC) \
     && (cmd != CMD_KLAD_SET_SP_KWMCWC) \
     && (cmd != CMD_KLAD_SET_COM_CA_CONTENT_KEY) \
     && (cmd != CMD_KLAD_SET_CONTENT_IV) \
     && (cmd != CMD_KLAD_GEN_K30_DA_NONCE) \
     && (cmd != CMD_KLAD_GEN_ENC_KEY) )
#elif defined(CFG_HI_TEE_SUMA_SUPPORT)
#define TEE_KLAD_CMD_INVALID(cmd) \
    ((cmd != CMD_KLAD_CREATE) \
     && (cmd != CMD_KLAD_DESTORY) \
     && (cmd != CMD_KLAD_ATTACH) \
     && (cmd != CMD_KLAD_DETACH) \
     && (cmd != CMD_KLAD_GET_ATTR) \
     && (cmd != CMD_KLAD_SET_ATTR) \
     && (cmd != CMD_KLAD_SET_SESSION_KEY) \
     && (cmd != CMD_KLAD_SET_CONTENT_KEY) \
     && (cmd != CMD_KLAD_GENERATE_ENCKEY) \
     && (cmd != CMD_KLAD_BOOT2CIPHER) \
     && (cmd != CMD_KLAD_SET_MISC_KWMCWC) \
     && (cmd != CMD_KLAD_SET_SP_KWMCWC) \
     && (cmd != CMD_KLAD_SET_COM_CA_CONTENT_KEY) \
     && (cmd != CMD_KLAD_SET_CONTENT_IV) \
     && (cmd != CMD_KLAD_GEN_DATAKEY) \
     && (cmd != CMD_KLAD_GEN_ENC_KEY) )
#elif defined(CFG_HI_TEE_IRDETO_SUPPORT)
#define TEE_KLAD_CMD_INVALID(cmd) \
    ((cmd != CMD_KLAD_CREATE) \
     && (cmd != CMD_KLAD_DESTORY) \
     && (cmd != CMD_KLAD_ATTACH) \
     && (cmd != CMD_KLAD_DETACH) \
     && (cmd != CMD_KLAD_GET_ATTR) \
     && (cmd != CMD_KLAD_SET_ATTR) \
     && (cmd != CMD_KLAD_SET_SESSION_KEY) \
     && (cmd != CMD_KLAD_SET_CONTENT_KEY) \
     && (cmd != CMD_KLAD_GENERATE_ENCKEY) \
     && (cmd != CMD_KLAD_GEN_ENC_KEY) \
     && (cmd != CMD_KLAD_CW_TA_SET_FLAG) \
     && (cmd != CMD_KLAD_CW_TA_SET_DATA) )
#else
#define TEE_KLAD_CMD_INVALID(cmd) \
    ((cmd != CMD_KLAD_CREATE) \
     && (cmd != CMD_KLAD_DESTORY) \
     && (cmd != CMD_KLAD_ATTACH) \
     && (cmd != CMD_KLAD_DETACH) \
     && (cmd != CMD_KLAD_GET_ATTR) \
     && (cmd != CMD_KLAD_SET_ATTR) \
     && (cmd != CMD_KLAD_SET_SESSION_KEY) \
     && (cmd != CMD_KLAD_SET_CONTENT_KEY) \
     && (cmd != CMD_KLAD_GENERATE_ENCKEY) \
     && (cmd != CMD_KLAD_BOOT2CIPHER) \
     && (cmd != CMD_KLAD_SET_MISC_KWMCWC) \
     && (cmd != CMD_KLAD_SET_SP_KWMCWC) \
     && (cmd != CMD_KLAD_SET_COM_CA_CONTENT_KEY) \
     && (cmd != CMD_KLAD_SET_CONTENT_IV) \
     && (cmd != CMD_KLAD_GEN_ENC_KEY) )
#endif
#define  TEE_KLAD_CMD_CHECK(cmd) \
    if (TEE_KLAD_CMD_INVALID(cmd)) \
    { \
        KLAD_PrintErrorCode(HI_ERR_KLAD_UNKNOWN_CMD);\
        return HI_ERR_KLAD_UNKNOWN_CMD; \
    }

struct klad_mutex
{
    struct tee_hal_mutex lock;
};

#define KLAD_NAME "HI_KLAD"

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
    CA_ID_BASIC              = 0x0, // basic
    CA_ID_NAGRA              = 0x1, // Nagra mode
    CA_ID_IRDETO             = 0x2, // Irdeto mode
    CA_ID_CONAX              = 0x3, // Conax mode
    CA_ID_SUMA               = 0x5, //SUMA
    CA_ID_VERIMATRIX         = 0x7, //Verimatrix
    CA_ID_DCAS               = 0xc, // dcas
    CA_ID_COMMON_CA          = 0x3f,//com ca
    CA_ID_BUTT
} CA_TYPE_E;

typedef struct
{
    HI_U32 cmd;
    HI_S32 (*f_driver_cmd_process)(HI_VOID* arg);
} DRV_KLAD_IOCTL_S;

#define HI_KLAD_MAX_SESSION  32 /*5bit*/
/*|-------------------------handle----------------------------|
  |module:16bit | session:16bit|
  |-----------------------------------------------------------|*/
#define HI_KLAD_MAKEHANDLE(mod, session)  \
    (HI_HANDLE)( (((mod)& 0xffff) << 16) |((session) & 0xffff))
#define HI_KLAD_GET_MODID(handle)     (((handle) >> 16) & 0xffff)
#define HI_KLAD_GET_CATYPE(handle)    (((handle) >> 8) & 0xff)
#define HI_KLAD_GET_KLADTYPE(handle)     (((handle) >> 5) & 0x1f)
#define HI_KLAD_GET_SESSIONID(handle)     (((handle)) & 0x1f)
#define HI_KLAD_GET_UNF_KLADTYPE(catype, kltype) ((((catype & 0xff) << 8) | (kltype & 0x1f)) & 0xffff)

typedef HI_S32 (* KLAD_IOCTL)(HI_U32 cmd, HI_VOID* arg);
typedef HI_VOID (* KLAD_SETSECEN)(HI_VOID);
typedef HI_S32 (* KLAD_MODULE_OPS)(HI_VOID);

typedef struct
{
    CA_TYPE_E ca;
    struct list_head list;
    KLAD_IOCTL      ioctl;
    KLAD_SETSECEN    setsecen;
} KLAD_DRV_ZONE;

typedef struct
{
    HI_HANDLE handle; /*key, session handle*/

    HI_HANDLE target;  /*attach target*/

    HI_BOOL attr_flag;
    DRV_KLAD_ATTR_S attr;

    HI_BOOL session_key_flag[HI_TEE_KLAD_LEVEL_BUTT];
    DRV_KLAD_SESSION_KEY_S session_key[HI_TEE_KLAD_LEVEL_BUTT];

    HI_BOOL content_key_flag;
    DRV_KLAD_CONTENT_KEY_S content_key;

    HI_U8 kwmcwc[16];

    TEE_UUID uuid;

    HI_BOOL content_iv_flag;
    DRV_KLAD_CONTENT_IV_S content_iv;

    HI_BOOL ta_klad_flag;
} DRV_KLAD_SESSION_INFO;

typedef struct
{
    struct list_head        list;
    DRV_KLAD_SESSION_INFO   instance;
} DRV_KLAD_SESSION;

HI_VOID DRV_KLAD_MutexLock();
HI_VOID DRV_KLAD_MutexUnLock();
HI_S32 DRV_KLAD_Init(HI_VOID);
HI_S32 DRV_KLAD_Exit(HI_VOID);
HI_S32 DRV_KLAD_Create(HI_VOID* arg);
HI_S32 DRV_KLAD_Destory(HI_VOID* arg);
HI_S32 DRV_KLAD_Attach(HI_VOID* arg);
HI_S32 DRV_KLAD_Detach(HI_VOID* arg);
HI_S32 DRV_KLAD_GetAttr(HI_VOID* arg);
HI_S32 DRV_KLAD_SetAttr(HI_VOID* arg);
HI_S32 DRV_KLAD_SetSessionKey(HI_VOID* arg);
HI_S32 DRV_KLAD_SetContentKey(HI_VOID* arg);
HI_S32 DRV_KLAD_GetSession(HI_HANDLE handle, DRV_KLAD_SESSION** session);
DRV_KLAD_TARGET_E DRV_KLAD_GetModID(DRV_KLAD_SESSION* session);
HI_S32 DRV_KLAD_SetSecEN(HI_VOID);
HI_S32 DRV_KLAD_Register(KLAD_DRV_ZONE* zone);
HI_S32 DRV_KLAD_UnRegister(KLAD_DRV_ZONE* zone);
HI_S32 DRV_KLAD_Ioctl(unsigned int cmd, void* arg);
HI_S32  DRV_KLAD_SetDataIn(HI_U8* data);
HI_S32 DRV_KLAD_SetContentIV(HI_VOID* arg);
HI_S32 DRV_KLAD_CmdRightCheck(HI_U32 cmd, HI_VOID* buffer, HI_U32 len);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif  /* __DRV_ADVCA_H__ */
