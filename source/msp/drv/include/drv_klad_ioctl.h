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
#include "hi_drv_klad.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */

typedef struct hiDRV_KLAD_ATTR_S
{
    HI_U32 klad_type;
    HI_UNF_KLAD_ALG_TYPE_E alg;
    HI_UNF_KLAD_TARGET_ENGINE_E engine;
} DRV_KLAD_ATTR_S;

/**drv session key*/
typedef struct hiDRV_KLAD_SESSION_KEY_S
{
    HI_UNF_KLAD_LEVEL_E level;
    HI_U8 key[HI_UNF_KLAD_MAX_KEY_LEN];
} DRV_KLAD_SESSION_KEY_S;

/**drv content key*/
typedef struct hiDRV_KLAD_CONTENT_KEY_S
{
    HI_BOOL odd;
    HI_U8 key[HI_UNF_KLAD_MAX_KEY_LEN];
} DRV_KLAD_CONTENT_KEY_S;

typedef struct
{
    HI_BOOL odd;
    HI_U32 length;
    HI_U8 iv[HI_UNF_KLAD_MAX_KEY_LEN];
} DRV_KLAD_CONTENT_IV_S;
/**Encrypted key*/
typedef struct hiDRV_KLAD_ENC_CLEAR_KEY_S
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

typedef struct
{
    HI_HANDLE handle;
    DRV_KLAD_CONTENT_IV_S content_iv;
} KLAD_CTL_CONTENT_IV_S;

typedef struct hiKLAD_CTL_ENC_CLEAR_KEY_S
{
    HI_HANDLE handle;
    DRV_KLAD_ENC_CLEAR_KEY_S key;
} KLAD_CTL_ENC_CLEAR_KEY_S;

typedef struct hiKLAD_CTL_KLAD_DBG_S
{
    HI_HANDLE handle;
    DRV_KLAD_DBG_S dbg;
} KLAD_CTL_DBG_S;

#ifdef HI_ADVCA_DCAS_SUPPORT
typedef struct hiKLAD_CTL_DA_NONCE_S
{
    HI_HANDLE handle;
    HI_U8 nonce[HI_UNF_KLAD_MAX_KEY_LEN];
    HI_U8 da_nonce[HI_UNF_KLAD_MAX_KEY_LEN];
} KLAD_CTL_DA_NONCE_S;
#endif

typedef struct hiKLAD_CTL_CUR_BIT_CNT_S
{
    HI_HANDLE handle;
    HI_U8 cur_bit_cnt;
} KLAD_CTL_CUR_BIT_CNT_S;

typedef struct hiKLAD_CTL_CW_TA_FLAG_S
{
    HI_HANDLE handle;
    HI_U8 flag;
} KLAD_CTL_CW_TA_FLAG_S;

typedef struct hiKLAD_CTL_WIDEVINE_DEC_FLAG_S
{
    HI_HANDLE handle;
    HI_U32 flag;
} KLAD_CTL_WIDEVINE_DEC_FLAG_S;


#define CMD_KLAD_CREATE                     _IOWR(HI_ID_CA, 0x1, KLAD_CTL_HANDLE_S)
#define CMD_KLAD_DESTORY                    _IOW (HI_ID_CA, 0x2, HI_HANDLE)
#define CMD_KLAD_ATTACH                     _IOWR(HI_ID_CA, 0x3, KLAD_CTL_TARGET_S)
#define CMD_KLAD_DETACH                     _IOWR(HI_ID_CA, 0x4, KLAD_CTL_TARGET_S)
#define CMD_KLAD_GET_ATTR                   _IOWR(HI_ID_CA, 0x5, KLAD_CTL_ATTR_S)
#define CMD_KLAD_SET_ATTR                   _IOW (HI_ID_CA, 0x6, KLAD_CTL_ATTR_S)
#define CMD_KLAD_GET_DEFAULT_ATTR           _IOWR(HI_ID_CA, 0x7, KLAD_CTL_ATTR_S)
#define CMD_KLAD_SET_SESSION_KEY            _IOW (HI_ID_CA, 0x8, KLAD_CTL_SESSION_KEY_S)
#define CMD_KLAD_SET_CONTENT_KEY            _IOW (HI_ID_CA, 0x9, KLAD_CTL_CONTENT_KEY_S)
#define CMD_KLAD_GET_DBG                    _IOWR(HI_ID_CA, 0xa, KLAD_CTL_DBG_S)
#define CMD_KLAD_GEN_ENC_KEY                _IOWR(HI_ID_CA, 0xb, KLAD_CTL_ENC_CLEAR_KEY_S)
#define CMD_KLAD_GEN_CLEAR_KEY              _IOWR(HI_ID_CA, 0xc, KLAD_CTL_ENC_CLEAR_KEY_S)

#define CMD_KLAD_BOOT2CIPHER                _IOW (HI_ID_CA, 0xd, HI_HANDLE)

#ifdef HI_ADVCA_DCAS_SUPPORT
#define CMD_KLAD_GEN_K30_DA_NONCE            _IOR (HI_ID_CA, 0xf, KLAD_CTL_DA_NONCE_S)
#endif

#define CMD_KLAD_GET_CUR_BIT_CNT            _IOR (HI_ID_CA, 0x11, KLAD_CTL_CUR_BIT_CNT_S)
#define CMD_KLAD_CW_TA_SET_FLAG             _IOW (HI_ID_CA, 0x12, KLAD_CTL_CW_TA_FLAG_S)

#define CMD_KLAD_WIDEVINE_GET_DEC_FLAG      _IOR (HI_ID_CA, 0x13, KLAD_CTL_WIDEVINE_DEC_FLAG_S)
#define CMD_KLAD_STBROOTKEY2CIPHER          _IOW (HI_ID_CA, 0x14, HI_HANDLE)

#define CMD_KLAD_SET_CONTENT_IV             _IOW (HI_ID_CA, 0x15, KLAD_CTL_CONTENT_IV_S)

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __DRV_KLAD_IOCTL_H__ */
