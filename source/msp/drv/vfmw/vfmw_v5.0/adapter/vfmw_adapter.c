#include "public.h"
#include "vfmw_debug.h"
#include "vfmw_adapter.h"
#include "vfmw_osal_ext.h"
#include "vfmw_img_info.h"
#include "pts_info.h"
#include "vfmw_write_yuv.h"

#ifdef HI_TEE_SUPPORT
#include "vfmw_tee_client.h"
#endif
#ifdef VFMW_CRC_SUPPORT
#include "crc.h"
#endif


/*======================================================================*/
/*   Type definition                                                        */
/*======================================================================*/
typedef struct
{
    UINT8 IsSec;
}GLB_CHAN_INFO;


/*======================================================================*/
/*   Internal data                                                      */
/*======================================================================*/
static GLB_CHAN_INFO g_ChanInfo[MAX_CHAN_NUM];


/*======================================================================*/
/*   Internal interface                                                 */
/*======================================================================*/
static UINT8 VFMW_GetTVPFlag(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs)
{
    SINT64 *p64 = NULL;
    UINT8 SecFlag = 0;

    if (ChanID >= 0 && ChanID < MAX_CHAN_NUM)
    {
        SecFlag = g_ChanInfo[ChanID].IsSec;
    }
    else
    {
        if (VDEC_CID_CREATE_CHAN == eCmdID || VDEC_CID_GET_CHAN_MEMSIZE == eCmdID)
        {
            p64 = (SINT64*)pArgs;
            SecFlag = ((VDEC_CHAN_OPTION_S*)UINT64_PTR(p64[1]))->s32IsSecMode;
        }
        else if (VDEC_CID_FREE_CHAN_NOTIFY == eCmdID)
        {
            SecFlag = 1;
        }
    }

    return SecFlag;
}

static VOID VFMW_BeforeCfgChan(SINT32 ChanID, VOID *pArgs)
{
    VDEC_CHAN_CFG_S *pCfg = (VDEC_CHAN_CFG_S *)pArgs;

    VFMW_ASSERT(pCfg != NULL);

    if (pCfg->bSampleFRDEnable == VDEC_TRUE)
    {
        PTS_Info_EnableSampleFRD(ChanID);
    }
    else
    {
        PTS_Info_DisableSampleFRD(ChanID);
    }

#ifdef VFMW_CRC_SUPPORT
    CRC_SetConfig(ChanID, pCfg);
#endif

    return;
}

static VOID VFMW_AfterCreateChan(SINT32 ChanID, VOID *pArgs, UINT8 IsSec, SINT32 Result)
{
    SINT32 *p32 = NULL;

    if (Result != VDEC_OK)
    {
        return;
    }

    p32 = (SINT32 *)pArgs;
    ChanID = p32[0];
    if (ChanID < 0 || ChanID >= MAX_CHAN_NUM)
    {
        dprint(PRN_ERROR, "%s: ChanID %d invalid!\n", __func__, ChanID);
        return;
    }

    PTS_Info_Alloc(ChanID);

#ifdef VFMW_CRC_SUPPORT
    if (CRC_CreateInst(ChanID) != VDEC_OK)
    {
        dprint(PRN_ERROR, "Create CRC inst %d failed!\n", ChanID);
    }
#endif

    g_ChanInfo[ChanID].IsSec = (IsSec) ? 1 : 0;

    return;
}

static VOID VFMW_AfterResetChan(SINT32 ChanID, VOID *pArgs, UINT8 IsSec, SINT32 Result)
{
    PTS_Info_Reset(ChanID);

    return;
}

static VOID VFMW_AfterDestroyChan(SINT32 ChanID, VOID *pArgs, UINT8 IsSec, SINT32 Result)
{
    PTS_Info_Free(ChanID);

#ifdef VFMW_CRC_SUPPORT
    if (CRC_DestroyInst(ChanID) != VDEC_OK)
    {
        dprint(PRN_ERROR, "Destroy CRC inst %d failed!\n", ChanID);
    }
#endif

    return;
}

static VOID VFMW_BeforeControl(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs)
{
    switch (eCmdID)
    {
        case VDEC_CID_CFG_CHAN:
            VFMW_BeforeCfgChan(ChanID, pArgs);
            break;

        default:
            break;
    }

    return;
}

static VOID VFMW_AfterControl(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs, UINT8 IsSec, SINT32 Result)
{
    switch (eCmdID)
    {
        case VDEC_CID_CREATE_CHAN:
            VFMW_AfterCreateChan(ChanID, pArgs, IsSec, Result);
            break;

        case VDEC_CID_RESET_CHAN:
        case VDEC_CID_RESET_CHAN_WITH_OPTION:
            VFMW_AfterResetChan(ChanID, pArgs, IsSec, Result);
            break;

        case VDEC_CID_DESTROY_CHAN:
            VFMW_AfterDestroyChan(ChanID, pArgs, IsSec, Result);
            break;

        default:
            break;
    }

    return;
}

SINT32 VFMW_AdapterControl(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs, UINT8 *pIsAdapterCase)
{
    SINT32 Ret = VDEC_ERR;

    *pIsAdapterCase = 1;

    switch (eCmdID)
    {
        case VDEC_CID_SET_FRAME_RATE_TYPE:
        {
            PTS_FRMRATE_S *pstFrmRate = (PTS_FRMRATE_S *)pArgs;

            Ret = PTS_Info_SetFrmRate(ChanID, pstFrmRate);
            break;
        }

        case VDEC_CID_GET_FRAME_RATE_TYPE:
        {
            PTS_FRMRATE_S *pstFrmRate = (PTS_FRMRATE_S *)pArgs;

            Ret = PTS_Info_GetFrmRate(ChanID, pstFrmRate);
            break;
        }

        default:
        {
            *pIsAdapterCase = 0;
            break;
        }
    }

    return Ret;
}


/*======================================================================*/
/*   External interface                                                 */
/*======================================================================*/
VOID VFMW_OpenModule(VOID)
{
    VDEC_OpenModule();

    OSAL_FP_proc_init();

#ifdef HI_TEE_SUPPORT
    TVP_VDEC_OpenModule();
#endif

#ifdef VDH_DISTRIBUTOR_ENABLE
    VDH_Init_Proc();
#endif

    IMG_Info_Init();

#ifdef VFMW_CRC_SUPPORT
    CRC_Init();
#endif

    OSAL_FP_memset(&g_ChanInfo, 0, MAX_CHAN_NUM * sizeof(GLB_CHAN_INFO));

    return;
}

VOID VFMW_ExitModule(VOID)
{
#ifdef VFMW_CRC_SUPPORT
    CRC_Exit();
#endif

    IMG_Info_Exit();

#ifdef VDH_DISTRIBUTOR_ENABLE
    VDH_Exit_Proc();
#endif

#ifdef HI_TEE_SUPPORT
    TVP_VDEC_ExitModule();
#endif

    OSAL_FP_proc_exit();

    VDEC_ExitModule();

    return;
}

SINT32 VFMW_Init(VDEC_OPERATION_S *pArgs)
{
    SINT32 ret = VDEC_ERR;

    if (NULL == pArgs)
    {
        dprint(PRN_ERROR, "%s pArgs = NULL\n", __func__);

        return HI_FAILURE;
    }

    if (pArgs->is_secure)
    {
    #ifdef HI_TEE_SUPPORT
        ret = TVP_VDEC_TrustDecoderInit(pArgs);
    #endif
    }
    else
    {
        ret = VDEC_Init(pArgs);
    }

    return (ret == VDEC_OK)? HI_SUCCESS: HI_FAILURE;
}

SINT32 VFMW_Exit(UINT8 IsSec)
{
    SINT32 ret = VDEC_ERR;

    if (IsSec)
    {
    #ifdef HI_TEE_SUPPORT
        ret = TVP_VDEC_TrustDecoderExit();
    #endif
    }
    else
    {
        ret = VDEC_Exit();
    }

    return (ret == VDEC_OK)? HI_SUCCESS: HI_FAILURE;
}

SINT32 VFMW_Control(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs, UINT32 ParamLength)
{
    SINT32 Ret;
    UINT8 IsAdapterCase = 0;
    UINT8 IsSec = 0;

    Ret = VFMW_AdapterControl(ChanID, eCmdID, pArgs, &IsAdapterCase);

    if (IsAdapterCase == 0)
    {
        VFMW_BeforeControl(ChanID, eCmdID, pArgs);

        IsSec = VFMW_GetTVPFlag(ChanID, eCmdID, pArgs);

        if (IsSec)
        {
        #ifdef HI_TEE_SUPPORT
            Ret = TVP_VDEC_Control(ChanID, eCmdID, pArgs, ParamLength);
        #endif
        }
        else
        {
            Ret = VDEC_Control(ChanID, eCmdID, pArgs);
        }

        VFMW_AfterControl(ChanID, eCmdID, pArgs, IsSec, Ret);
    }

    return (Ret == VDEC_OK)? HI_SUCCESS: HI_FAILURE;
}

SINT32 VFMW_Suspend(VOID)
{
    SINT32 ret;

    ret = VDEC_Suspend();
    if (ret != VDEC_OK)
    {
        HI_FATAL_VFMW("%s Call VDEC_Suspend Failed!\n", __func__);
    }

#ifdef HI_TEE_SUPPORT
    ret = TVP_VDEC_Suspend();
    if (ret != VDEC_OK)
    {
        HI_FATAL_VFMW("%s Call TVP_VDEC_Suspend Failed!\n", __func__);
    }
#endif

#ifdef VDH_DISTRIBUTOR_ENABLE
    if (g_HalDisable != 1)
    {
        VDH_Suspend();
    }
#endif

    return VDEC_OK;
}

SINT32 VFMW_Resume(VOID)
{
    SINT32 ret;

#ifdef VDH_DISTRIBUTOR_ENABLE
    if (g_HalDisable != 1)
    {
        VDH_Resume();
    }
#endif

    ret = VDEC_Resume();
    if (ret != VDEC_OK)
    {
        HI_FATAL_VFMW("%s Call VDEC_Resume Failed!\n", __func__);
    }

#ifdef HI_TEE_SUPPORT
    ret = TVP_VDEC_Resume();
    if (ret != VDEC_OK)
    {
        HI_FATAL_VFMW("%s Call TVP_VDEC_Resume Failed!\n", __func__);
    }
#endif

    return VDEC_OK;
}

SINT32 VFMW_GetImage(SINT32 ChanID, IMAGE *pImage)
{
    SINT32 ret = VDEC_ERR;

    VFMW_ASSERT_RETURN(ChanID >= 0 && ChanID < MAX_CHAN_NUM, VDEC_ERR);

#ifdef HI_TEE_SUPPORT
    if (g_ChanInfo[ChanID].IsSec)
    {
        ret = TVP_VDEC_GetImage(ChanID, pImage);
    }
    else
#endif
    {
        ret = VDEC_GetImage(ChanID, pImage);

        if (ret == VDEC_OK)
        {
            YUV_DumpImage(ChanID, pImage);
        }
    }

    if (ret == VDEC_OK)
    {
#ifdef VFMW_CRC_SUPPORT
        CRC_PutImage(ChanID, pImage);
#endif
        IMG_Info_Convert(ChanID, pImage);
    }

    return ret;
}

SINT32 VFMW_ReleaseImage(SINT32 ChanID, IMAGE *pImage)
{
    SINT32 ret = VDEC_ERR;

    VFMW_ASSERT_RETURN(ChanID >= 0 && ChanID < MAX_CHAN_NUM, VDEC_ERR);

#ifdef HI_TEE_SUPPORT
    if (g_ChanInfo[ChanID].IsSec)
    {
        ret = TVP_VDEC_ReleaseImage(ChanID, pImage);
    }
    else
#endif
    {
        ret = VDEC_ReleaseImage(ChanID, pImage);
    }

    return ret;
}

