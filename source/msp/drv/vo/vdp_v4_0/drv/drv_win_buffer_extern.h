#ifndef __DRV_WIN_BUFFER_EXTERN_H__
#define __DRV_WIN_BUFFER_EXTERN_H__

#include "hi_type.h"
#include "hi_common.h"
#include "hi_drv_video.h"
#include "hi_drv_win.h"
#include "drv_disp_osal.h"
#include "drv_window.h"
#include "drv_vpss_ext.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


#define EXTERN_DBG(fmt...)  HI_INFO_PRINT(HI_ID_VO, fmt)
#define EXTERN_ERROR(fmt...)  HI_ERR_PRINT(HI_ID_VO, fmt)

#define WIN_EXTERN_CHECKRET(ret,exp,func_name)\
    {\
        if (ret != exp)\
        {\
            WIN_ERROR("%s err!,ret = %#x\n",func_name,ret); \
            return ret; \
        }\
    }

#define WIN_EXTERN_CHECK_LIST_EMPTY(head,tail,lenth)  ((head == tail))

#define WIN_EXTERN_CHECK_LIST_FULL(head,tail,lenth) ((tail + 1) % lenth == head)

#define WIN_EXTERN_CHECK_LIST_ALLDONE(processed,tail,lenth) ((processed + 1) % lenth == tail)

#define HICEILING(x, a)           (((x)+(a)-1)/(a))

#define WIN_EXTERN_BUFFER_MAX 32
#define WIN_EXTERN_INSTANCE_MAX 16

#define    BUFFER_LEN_4K          (0x1000)

typedef struct tagWIN_EXTERN_S
{
    HI_DRV_VIDEO_FRAME_S stSrcFrame[WIN_EXTERN_BUFFER_MAX];
    HI_U32               u32SrcPlayCnt[WIN_EXTERN_BUFFER_MAX];
    HI_U32 u32SrcListHead;
    HI_U32 u32SrcListTail;
    HI_U32 u32SrcAcquiredPos;
    spinlock_t stSrcLock;

    HI_DRV_VIDEO_FRAME_S stSrcDoneFrame[WIN_EXTERN_BUFFER_MAX];
    HI_BOOL   bSrcDoneFlag[WIN_EXTERN_BUFFER_MAX];
    spinlock_t stSrcDoneLock;


    HI_HANDLE hVpss;
    HI_HANDLE hPort;

    HI_HANDLE hWin;
    HI_HANDLE hSrc;
    PFN_GET_FRAME_CALLBACK pfAcqFrame;
    PFN_PUT_FRAME_CALLBACK pfRlsFrame;

    HI_DRV_VIDEO_FRAME_S stAcqTmpFrame;
    HI_DRV_VIDEO_FRAME_S stRlsVpssTmpFrame;

} WIN_EXTERN_S;

typedef struct hiEXTERN_SOURCE_INFO_S
{
    HI_HANDLE hWin;
    HI_HANDLE hSrc;
    PFN_GET_FRAME_CALLBACK pfAcqFrame;
    PFN_PUT_FRAME_CALLBACK pfRlsFrame;
} EXTERN_SOURCE_INFO_S;


HI_S32 WIN_AcqCaptureFrame( HI_DRV_VIDEO_FRAME_S* pstFrm, HI_U32 u32StartSmmuAddr, HI_U32 u32Stride_Y, HI_U32 u32Width, HI_U32 u32Height);
HI_S32 WIN_EXTERN_VPSS_Start(WIN_EXTERN_S* pstExtern);
HI_S32 WIN_EXTERN_VPSS_Stop( HI_HANDLE hVpss);
HI_S32 WIN_EXTERN_CreateVpss(WIN_EXTERN_S* pstExtern);
HI_S32 WIN_EXTERN_DestoryVpss(WIN_EXTERN_S* pstExtern);
HI_S32 WIN_EXTERN_CreatePort(WIN_EXTERN_S* pstExtern);
HI_S32 WIN_EXTERN_ListInit(WIN_EXTERN_S* pstExtern);
HI_S32 WIN_EXTERN_ListDeInit(WIN_EXTERN_S* pstExtern);
HI_S32 WIN_EXTERN_Init(WIN_EXTERN_S* pstExtern);
HI_S32 WIN_EXTERN_WaitForFinish(HI_U32 u32Delay10ms);
HI_S32 WIN_EXTERN_DeInit(WIN_EXTERN_S* pstExtern);
HI_S32 WIN_EXTERN_SetAttr(WIN_EXTERN_S* pstExtern, HI_U32 u32Width, HI_U32 u32Height);
HI_S32 WIN_VpssEventHandle(HI_HANDLE hWin, HI_DRV_VPSS_EVENT_E enEventID, HI_VOID* pstArgs);
HI_S32 WIN_VpssRlsSrcFrame(VPSS_HANDLE hVpss, HI_DRV_VIDEO_FRAME_S* pstFrm);
HI_S32 WIN_VpssAcqSrcFrame(VPSS_HANDLE hVpss, HI_DRV_VIDEO_FRAME_S* pstFrm);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*  __DRV_WINDOW_H__  */
