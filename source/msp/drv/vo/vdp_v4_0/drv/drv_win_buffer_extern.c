#include "drv_window.h"
#include "drv_win_priv.h"
#include "hi_drv_sys.h"
#include "hi_drv_module.h"
#include "drv_win_buffer_extern.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

VPSS_EXPORT_FUNC_S *s_pstExternVpssFunc = HI_NULL;
HI_BOOL g_bComplete = HI_FALSE;
HI_HANDLE g_hVpss = HI_INVALID_HANDLE;

HI_S32 WIN_EXTERN_CreateVpss(WIN_EXTERN_S* pstExtern)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_DRV_VPSS_CFG_S stVpssCfg;
    HI_DRV_VPSS_SOURCE_FUNC_S stRegistSrcFunc;

    memset((HI_VOID*)&stVpssCfg, 0, sizeof(HI_DRV_VPSS_CFG_S));
    memset((HI_VOID*)&stRegistSrcFunc, 0, sizeof(HI_DRV_VPSS_SOURCE_FUNC_S));

    s32Ret = s_pstExternVpssFunc->pfnVpssGlobalInit();
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "pfnVpssGlobalInit");

    s32Ret = (s_pstExternVpssFunc->pfnVpssGetDefaultCfg)(&stVpssCfg);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "pfnVpssGetDefaultCfg");

    stVpssCfg.enProgInfo = HI_DRV_VPSS_PRODETECT_PROGRESSIVE;
    stVpssCfg.bProgRevise = HI_FALSE;
    s32Ret = (s_pstExternVpssFunc->pfnVpssCreateVpss)(&stVpssCfg, &(pstExtern->hVpss));
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "pfnVpssCreateVpss");

    s32Ret = (s_pstExternVpssFunc->pfnVpssRegistHook)((pstExtern->hVpss), pstExtern->hWin, WIN_VpssEventHandle);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "pfnVpssRegistHook");

    stRegistSrcFunc.VPSS_GET_SRCIMAGE = WIN_VpssAcqSrcFrame;
    stRegistSrcFunc.VPSS_REL_SRCIMAGE = WIN_VpssRlsSrcFrame;
    s32Ret = (s_pstExternVpssFunc->pfnVpssSetSourceMode)((pstExtern->hVpss), VPSS_SOURCE_MODE_VPSSACTIVE, &stRegistSrcFunc);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "pfnVpssSetSourceMode");

    return HI_SUCCESS;

}

HI_S32 WIN_EXTERN_DestoryVpss(WIN_EXTERN_S* pstExtern)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = (s_pstExternVpssFunc->pfnVpssSendCommand)(pstExtern->hVpss, HI_DRV_VPSS_USER_COMMAND_STOP, HI_NULL);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "pfnVpssSendCommand");

    s32Ret = (s_pstExternVpssFunc->pfnVpssDestroyVpss)(pstExtern->hVpss);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "pfnVpssDestroyVpss");

    s32Ret = s_pstExternVpssFunc->pfnVpssGlobalDeInit();
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "pfnVpssGlobalDeInit");

    return HI_SUCCESS;

}

HI_S32 WIN_EXTERN_CreatePort(WIN_EXTERN_S* pstExtern)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_DRV_VPSS_PORT_CFG_S stVpssPortCfg;

    memset((HI_VOID*)&stVpssPortCfg, 0, sizeof(HI_DRV_VPSS_PORT_CFG_S));

    s32Ret = (s_pstExternVpssFunc->pfnVpssGetDefaultPortCfg)(&stVpssPortCfg);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "pfnVpssGetDefaultPortCfg");

    stVpssPortCfg.stBufListCfg.eBufType = HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE;
    //stVpssPortCfg.stBufListCfg.eBufType = HI_DRV_VPSS_BUF_VPSS_ALLOC_MANAGE;
    stVpssPortCfg.s32OutputWidth  = 1280;
    stVpssPortCfg.s32OutputHeight = 720;
    stVpssPortCfg.stBufListCfg.u32BufSize = stVpssPortCfg.s32OutputHeight * stVpssPortCfg.s32OutputWidth * 3 / 2;
    stVpssPortCfg.stBufListCfg.u32BufStride = stVpssPortCfg.s32OutputWidth;
    stVpssPortCfg.eFormat = HI_DRV_PIX_FMT_NV21;
    stVpssPortCfg.eAspMode = HI_DRV_ASP_RAT_MODE_FULL;
    stVpssPortCfg.eDstCS = HI_DRV_CS_BT709_YUV_LIMITED;
    s32Ret = (s_pstExternVpssFunc->pfnVpssCreatePort)(pstExtern->hVpss, &stVpssPortCfg, &(pstExtern->hPort));
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "pfnVpssCreatePort");

    s32Ret = (s_pstExternVpssFunc->pfnVpssEnablePort)(pstExtern->hPort, HI_TRUE);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "pfnVpssEnablePort");

    return HI_SUCCESS;
}

HI_S32 WIN_EXTERN_ListInit(WIN_EXTERN_S* pstExtern)
{
    memset(&(pstExtern->stSrcFrame), 0, sizeof(HI_DRV_VIDEO_FRAME_S)*WIN_EXTERN_BUFFER_MAX);

    spin_lock_init(&(pstExtern->stSrcLock));
    pstExtern->u32SrcListHead = 0;
    pstExtern->u32SrcListTail = 0;
    pstExtern->u32SrcAcquiredPos = WIN_EXTERN_BUFFER_MAX - 1;
    spin_lock_init(&(pstExtern->stSrcDoneLock));
    memset(pstExtern->bSrcDoneFlag, 0, sizeof(HI_BOOL)*WIN_EXTERN_BUFFER_MAX);

    return HI_SUCCESS;
}
HI_S32 WIN_EXTERN_ListDeInit(WIN_EXTERN_S* pstExtern)
{
    memset(&(pstExtern->stSrcFrame), 0, sizeof(HI_DRV_VIDEO_FRAME_S)*WIN_EXTERN_BUFFER_MAX);

    pstExtern->u32SrcListHead = 0;
    pstExtern->u32SrcListTail = 0;

    return HI_SUCCESS;
}

HI_S32 WIN_EXTERN_VPSS_Start(WIN_EXTERN_S *pstExtern)
{
    HI_S32 s32Ret = HI_SUCCESS;

    g_bComplete = HI_FALSE;
    s_pstExternVpssFunc->pfnVpssSendCommand(pstExtern->hVpss, HI_DRV_VPSS_USER_COMMAND_START, HI_NULL);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "pfnVpssSendCommand");

    return HI_SUCCESS;
}

HI_S32 WIN_EXTERN_VPSS_Stop( HI_HANDLE hVpss)
{
    HI_S32 s32Ret = HI_SUCCESS;

    g_bComplete = HI_TRUE;
    s_pstExternVpssFunc->pfnVpssSendCommand(hVpss, HI_DRV_VPSS_USER_COMMAND_STOP, HI_NULL);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "pfnVpssSendCommand");

    return HI_SUCCESS;
}

HI_S32 WIN_EXTERN_WaitForFinish( HI_U32 u32Delay10ms)
{
    HI_U32 u32Delay = 0;

    while (HI_TRUE != g_bComplete)
    {
        if (u32Delay < u32Delay10ms)
        {
            msleep(10);
            u32Delay++;
        }
        else
        {
            WIN_ERROR("time out !");
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

HI_S32 WIN_EXTERN_Init(WIN_EXTERN_S* pstExtern)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = WIN_EXTERN_ListInit(pstExtern);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "WIN_EXTERN_ListInit");

    s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_VPSS, (HI_VOID**)&s_pstExternVpssFunc);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "Get Vpss Function");

    s32Ret = WIN_EXTERN_CreateVpss(pstExtern);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "WIN_EXTERN_CreateVpss");

    s32Ret = WIN_EXTERN_CreatePort(pstExtern);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "WIN_EXTERN_CreatePort");
    g_hVpss = pstExtern->hVpss;

    return HI_SUCCESS;
}

HI_S32 WIN_EXTERN_DeInit(WIN_EXTERN_S* pstExtern)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = WIN_EXTERN_DestoryVpss(pstExtern);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "WIN_EXTERN_DestoryVpss");

    pstExtern->hVpss = HI_INVALID_HANDLE;
    pstExtern->hPort = HI_INVALID_HANDLE;

    s32Ret = WIN_EXTERN_ListDeInit(pstExtern);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "WIN_EXTERN_ListDeInit");

    return HI_SUCCESS;
}

HI_DRV_VIDEO_FRAME_S *pstsCapture = HI_NULL;
HI_U32 g_u32TmpStartSmmuAddr = 0;
HI_U32 g_u32TmpWidth = 0;
HI_U32 g_u32TmpHeight = 0;
HI_U32 g_u32TmpStride_Y = 0;

HI_S32 WIN_EXTERN_SetAttr(WIN_EXTERN_S* pstExtern, HI_U32 u32Width, HI_U32 u32Height)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_DRV_VPSS_PORT_CFG_S stVpssPortCfg;

    s32Ret = (s_pstExternVpssFunc->pfnVpssGetPortCfg)(pstExtern->hPort, &stVpssPortCfg);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "pfnVpssGetPortCfg");
    stVpssPortCfg.s32OutputWidth  = u32Width;
    stVpssPortCfg.s32OutputHeight = u32Height;
    stVpssPortCfg.enOutBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
    s32Ret = (s_pstExternVpssFunc->pfnVpssSetPortCfg)(pstExtern->hPort, &stVpssPortCfg);
    WIN_EXTERN_CHECKRET(s32Ret, HI_SUCCESS, "pfnVpssSetPortCfg");

    return HI_SUCCESS;
}

HI_S32 WIN_AcqCaptureFrame( HI_DRV_VIDEO_FRAME_S* pstFrm, HI_U32 u32StartSmmuAddr, HI_U32 u32Stride_Y, HI_U32 u32Width, HI_U32 u32Height)
{
    pstsCapture  = pstFrm;
    pstsCapture->enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
    g_u32TmpStartSmmuAddr = u32StartSmmuAddr;
    g_u32TmpWidth = u32Width;
    g_u32TmpHeight = u32Height;
    g_u32TmpStride_Y = u32Stride_Y;

    return HI_SUCCESS;
}

static HI_S32 processor_get_frame_buffer( HI_VOID* pstArgs)
{
    HI_DRV_VPSS_FRMBUF_S* pVpssFrm = (HI_DRV_VPSS_FRMBUF_S*)pstArgs;

    pVpssFrm->u32StartPhyAddr = g_u32TmpStartSmmuAddr;
    pVpssFrm->pu8StartVirAddr = 0;
    pVpssFrm->u32Stride = g_u32TmpStride_Y;

    pVpssFrm->u32PrivDataPhyAddr = 0;
    pVpssFrm->pu8PrivDataVirAddr = 0;
    pVpssFrm->u32PrivDataSize    = 0;

    return HI_SUCCESS;
}

HI_S32 WIN_VpssEventHandle(HI_HANDLE hWin, HI_DRV_VPSS_EVENT_E enEventID, HI_VOID* pstArgs)
{
    HI_S32 ret = HI_FAILURE;

    if (HI_NULL == pstArgs)
    {
        WIN_ERROR( "enEventID = %d, pstArgs = NULL!\n", enEventID);
        return HI_FAILURE;
    }

    /* Event handle */
    switch (enEventID)
    {
        case VPSS_EVENT_CHECK_FRAMEBUFFER:
            ((HI_DRV_VPSS_BUFINFO_S*)pstArgs)->bAvailable = HI_TRUE;
            break;

        case  VPSS_EVENT_BUFLIST_FULL:
            break;

        case  VPSS_EVENT_GET_FRMBUFFER:
            ret = processor_get_frame_buffer( pstArgs);
            if (ret != HI_SUCCESS)
            {
                return HI_FAILURE;
            }

            break;
        case  VPSS_EVENT_REL_FRMBUFFER:
            break;
        case  VPSS_EVENT_TASK_COMPLETE:
        case  VPSS_EVENT_NEW_FRAME:

            WIN_EXTERN_VPSS_Stop(g_hVpss);
            break;

        default:
            WIN_ERROR( "Unknow enEventID: %d\n", enEventID);
         return HI_FAILURE;
    }

    return HI_SUCCESS;

}

HI_S32 WIN_VpssAcqSrcFrame(VPSS_HANDLE hVpss, HI_DRV_VIDEO_FRAME_S* pstFrm)
{
    if (HI_NULL != pstsCapture )
    {
        memcpy(pstFrm, pstsCapture, sizeof(HI_DRV_VIDEO_FRAME_S));
    }

    return HI_SUCCESS;
}

HI_S32 WIN_VpssRlsSrcFrame(VPSS_HANDLE hVpss, HI_DRV_VIDEO_FRAME_S* pstFrm)
{
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

