#ifndef __VENC_RC_EXT_H__
#define __VENC_RC_EXT_H__

#include "venc_osal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define  VENC_NULL_FUN_PTR    (-1)

typedef enum {
    RC_TYPE_CBR,
    RC_TYPE_VBR,
} RC_CONTROL_TYPE;

typedef enum {
    ENCODE_TYPE_I,
    ENCODE_TYPE_P,
} RC_ENCODE_TYPE;

typedef enum {
    RC_EVENT_TYPE_TIMING,                     /*this event means time after a second */   //清水线
} RC_EVENT_TYPE;

typedef struct
{
    UINT32 MinQp;
    UINT32 MaxQp;
    UINT32 PicWidth;
    UINT32 PicHeight;
    UINT32 VoFrmRate;
    UINT32 BitRate;
    UINT32 Gop;
    RC_CONTROL_TYPE RCType;
} VENC_RC_CFG_S;

typedef struct
{
    UINT32 TargetBits;
    UINT32 StartQP;
} VENC_RC_OUTPUT_S;

typedef struct
{
    RC_ENCODE_TYPE EncType;
    UINT32 IFrmInsertFlag;     /*if IFrmInsertFlag == 1 means this I frame is called by RequestIFrame API,
                                 so this flag just avalibale when EncType = ENCODE_TYPE_I*/
    UINT32 ReEncodeFlag;
    UINT32 ReduceBitsFlag;     /*if ReduceBitsFlag == 1 means this frame want to encode at lower bits than normal frame*/
} VENC_RC_INPUT_S;

typedef struct hiVENC_RC_FUN_PTR_S
{
    SINT32 (*pfun_RC_CreateInstance)(HANDLE *phRC, VENC_RC_CFG_S *pConfigure);
    SINT32 (*pfun_RC_DestoryInstance)(HANDLE hRC);

    SINT32 (*pfun_RC_SetConfig)(HANDLE hRC, VENC_RC_CFG_S *pConfigure);
    SINT32 (*pfun_RC_GetConfig)(HANDLE hRC, VENC_RC_CFG_S *pConfigure);

    SINT32 (*pfun_RC_Reset)(HANDLE hRC, VENC_RC_CFG_S *pConfigure);
    SINT32 (*pfun_RC_SetLastPicBits)(HANDLE hRC, UINT32 PicBits);

    SINT32 (*pfun_RC_CalcOneFrame)(HANDLE hRC, VENC_RC_INPUT_S *pParamIn VENC_RC_OUTPUT_S *pParamOut);

    SINT32 (*pfun_RC_NotifyEvent)(HANDLE hRC, RC_EVENT_TYPE eventType);

    /*还需要考虑一下变分辨率，动态编码率之类的是否也用以上几个接口就够了?是否需要添加RC控制状态查询接口?*/
} VENC_RC_FUN_PTR_S;

extern VENC_RC_FUN_PTR_S g_venc_rc_fun_ptr;

#define VENC_RC_CreateInstance(phRC, pConfigure) \
    (g_venc_rc_fun_ptr.pfun_RC_CreateInstance? \
     g_venc_rc_fun_ptr.pfun_RC_CreateInstance(phRC, pConfigure): \
     VENC_NULL_FUN_PTR)

#define VENC_RC_DestoryInstance(hRC) \
    (g_venc_rc_fun_ptr.pfun_RC_DestoryInstance? \
     g_venc_rc_fun_ptr.pfun_RC_DestoryInstance(hRC): \
     VENC_NULL_FUN_PTR)

#define VENC_RC_SetConfig(hRC, pConfigure) \
    (g_venc_rc_fun_ptr.pfun_RC_SetConfig? \
     g_venc_rc_fun_ptr.pfun_RC_SetConfig(hRC, pConfigure): \
     VENC_NULL_FUN_PTR)

#define VENC_RC_GetConfig(hRC, pConfigure) \
    (g_venc_rc_fun_ptr.pfun_RC_GetConfig? \
     g_venc_rc_fun_ptr.pfun_RC_GetConfig(hRC, pConfigure): \
     VENC_NULL_FUN_PTR)

#define VENC_RC_Reset(hRC, pConfigure) \
    (g_venc_rc_fun_ptr.pfun_RC_Reset? \
     g_venc_rc_fun_ptr.pfun_RC_Reset(hRC, pConfigure): \
     VENC_NULL_FUN_PTR)

#define VENC_RC_SetLastPicBits(hRC, PicBits) \
    (g_venc_rc_fun_ptr.pfun_RC_SetLastPicBits? \
     g_venc_rc_fun_ptr.pfun_RC_SetLastPicBits(hRC, PicBits): \
     VENC_NULL_FUN_PTR)

#define VENC_RC_CalcOneFrame(hRC, pParamIn, pParamOut) \
    (g_venc_rc_fun_ptr.pfun_RC_CalcOneFrame? \
     g_venc_rc_fun_ptr.pfun_RC_CalcOneFrame(hRC, pParamIn, pParamOut): \
     VENC_NULL_FUN_PTR)

#define VENC_RC_NotifyEvent(hRC, eventType) \
    (g_venc_rc_fun_ptr.pfun_RC_NotifyEvent? \
     g_venc_rc_fun_ptr.pfun_RC_NotifyEvent(hRC, eventType): \
     VENC_NULL_FUN_PTR)

#ifdef __cplusplus
}
#endif

#endif  // __VENC_RC_EXT_H__

