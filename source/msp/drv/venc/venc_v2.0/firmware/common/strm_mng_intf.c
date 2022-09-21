/* Common headers */
#include "strm_mng_intf.h"

/* Local headers */
#include "strm_mng_listbuf.h"
#include "strm_mng_recyclebuf.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define STRM_MODE_NUM 3
#define STRM_MODE_LIST 0
#define STRM_MODE_RECYCLE 1

VENC_STRM_FUN_PTR_S g_venc_strm_fun_ptr[STRM_MODE_NUM];

static VOID IntfInitList(VOID)
{
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_Init      = ListBuf_Init;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_DeInit    = ListBuf_DeInit;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_Create    = ListBuf_Create;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_Destroy   = ListBuf_Destroy;

    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_GetWriteBuffer = ListBuf_GetWriteBuf;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_PutWriteBuffer = ListBuf_PutWriteBuf;

    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_PutBufferForRecode = ListBuf_PutBufForRecode;

    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_AcqReadBuffer    = ListBuf_AcquireBitStream;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_RlsReadBuffer    = ListBuf_ReleaseBitStream;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_GetAcqStreamInfo = ListBuf_GetAcquireStreamInfo;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_GetRlsBufferInfo = ListBuf_GetRleaseStreamInfo;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_GetRlsBufferInfoIntar = ListBuf_GetRleaseStreamInfoIntar;

    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_CheckBufferSize  = ListBuf_CheckBufferSize;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_CalSlcSize       = ListBuf_CalSlcSize;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_GetStrmState     = ListBuf_GetStrmState;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_GetWrittenLen    = ListBuf_GetWrittenLen;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_GetBitBufSize    = ListBuf_GetBitBufSize;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_AllocStreamBuf   = ListBuf_AllocStreamBuf;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_AllocParaSetBufAddr = ListBuf_AllocParaSetBufAddr;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_RlsParaSetBufAddr = ListBuf_RlsParaSetBufAddr;

    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_ResetBuffer  = ListBuf_ResetBuffer;

#ifdef VENC_SUPPORT_JPGE
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_JPGEWriteHeader    = ListBuf_WriteHeader;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_PutJPGEWriteBuffer = ListBuf_PutJPGEWriteBuffer;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_JPGERemoveHeader   = ListBuf_JPGERemoveHeader;
    g_venc_strm_fun_ptr[STRM_MODE_LIST].pfun_STRM_GetJpgeStream      = ListBuf_GetJpgeStream;
#endif
}

static VOID IntfInitLoop(VOID)
{
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_Init      = RecycleBuf_Init;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_DeInit    = RecycleBuf_DeInit;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_Create    = RecycleBuf_Create;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_Destroy   = RecycleBuf_Destroy;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_GetWriteBuffer    = RecycleBuf_GetWriteBuf;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_PutWriteBuffer    = RecycleBuf_PutWriteBuf;

    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_PutBufferForRecode = RecycleBuf_PutBufForRecode;

    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_AcqReadBuffer    = RecycleBuf_AcqReadBuffer;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_RlsReadBuffer    = RecycleBuf_RlsReadBuffer;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_GetAcqStreamInfo = RecycleBuf_GetAcqStrmInfo;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_GetRlsBufferInfo = RecycleBuf_GetRlsStrmInfo;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_GetRlsBufferInfoIntar = RecycleBuf_GetRlsStrmInfoIntar;

    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_CheckBufferSize  = RecycleBuf_CheckBufSize;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_CalSlcSize       = RecycleBuf_CalSlcSize;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_GetStrmState     = RecycleBuf_GetStrmState;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_GetWrittenLen    = RecycleBuf_GetWrittenLength;

    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_ResetBuffer       = RecycleBuf_ResetBuffer;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_GetBitBufSize     = RecycleBuf_GetBitBufSize;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_AllocStreamBuf    = RecycleBuf_AllocStreamBuf;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_AllocParaSetBufAddr = RecycleBuf_AllocParaSetBufAddr;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_RlsParaSetBufAddr   = RecycleBuf_RlsParaSetBufAddr;

#ifdef VENC_SUPPORT_JPGE
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_JPGEWriteHeader    = RecycleBuf_WriteHeader;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_PutJPGEWriteBuffer = RecycleBuf_PutJPGEWriteBuffer;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_JPGERemoveHeader   = RecycleBuf_JPGERemoveHeader;
    g_venc_strm_fun_ptr[STRM_MODE_RECYCLE].pfun_STRM_GetJpgeStream      = RecycleBuf_GetJpgeStream;

#endif
}

static VOID IntfInitOther(VOID)
{

}

static HI_U32 FindStreamBufferFunc(HI_U32 hHandle, HI_U32 *pStrmMode, HI_U32 *pPrivateID)
{
    *pStrmMode  = hHandle >> 16;
    *pPrivateID = hHandle & 0xffff;

    if (*pStrmMode >= STRM_MODE_NUM)
    {
        HI_ERR_VENC("The Strm mode number %d exceeds the max number %d\n", *pStrmMode, STRM_MODE_NUM);

        return HI_ERR_VENC_INVALID_PARA;
    }

    if (*pPrivateID >= HI_VENC_MAX_CHN)
    {
        HI_ERR_VENC("The channel number %d exceeds the max number %d\n", *pPrivateID, HI_VENC_MAX_CHN);

        return HI_ERR_VENC_INVALID_PARA;
    }

    return HI_SUCCESS;
}

static HI_VOID InitStreamBuffer(HI_U32 StrmMode)
{
   g_venc_strm_fun_ptr[StrmMode].pfun_STRM_Init();
}

static HI_VOID DeInitStreamBuffer(HI_U32 StrmMode)
{
   g_venc_strm_fun_ptr[StrmMode].pfun_STRM_DeInit();
}

HI_S32 STRM_Init(HI_VOID)
{
    HI_U32 i = 0;
    HI_U32 Count = 0;

    IntfInitList();
    IntfInitLoop();
    IntfInitOther();

    for (i = 0; i < STRM_MODE_NUM; i++)
    {
        if (g_venc_strm_fun_ptr[i].pfun_STRM_Init != HI_NULL)
        {
            InitStreamBuffer(i);
        }
        else
        {
            Count++;
        }
    }

    if (Count == STRM_MODE_NUM)
    {
        HI_ERR_VENC("STRM Init is failure! There is no right strm mode!");

        return HI_ERR_VENC_NULL_PTR;
    }

    return HI_SUCCESS;
}

HI_S32 STRM_DeInit(HI_VOID)
{
    HI_U32 i = 0;
    HI_U32 Count = 0;

    for (i = 0; i < STRM_MODE_NUM; i++)
    {
        if (g_venc_strm_fun_ptr[i].pfun_STRM_Init != HI_NULL)
        {
            DeInitStreamBuffer(i);
        }
        else
        {
            Count++;
        }
    }

    if (Count == STRM_MODE_NUM)
    {
        HI_ERR_VENC("STRM DeInit is failure! There is no right strm mode!");

        return HI_ERR_VENC_NULL_PTR;
    }

    return HI_SUCCESS;
}

HI_S32 STRM_GetMatchMode(HI_U32 Protocol, HI_HANDLE* phStrmMng, HI_BOOL IsChipIDV500R001)
{
    HI_U32 StrmMode = 0;

    if (phStrmMng == HI_NULL)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

#ifdef VENC_SUPPORT_JPGE
    if (Protocol == VEDU_JPGE)
    {
        StrmMode = 1;
    }
    else
#endif
    {
        if (IsChipIDV500R001 == HI_TRUE)
        {
            StrmMode = 0;
        }
        else
        {
            switch (HI_VENC_STRM_MODE)
            {
                case STRM_MODE_LIST:
                    StrmMode = 0;
                    break;

                case STRM_MODE_RECYCLE:
                    StrmMode = 1;
                    break;

                default:
                    StrmMode = 0xffff;
                    break;
            }
        }
    }

    *phStrmMng = StrmMode << 16;

    if (*phStrmMng == 0xffff0000)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 GetConfigInfo(HI_HANDLE hStrmMng, STRMMNG_STREAM_INFO_S *pstStreamInfo, STRMMNG_INST_CONFIG_S *pstConfig)
{
    /*create inst*/

    if (hStrmMng == STRM_MODE_LIST)
    {
        pstConfig->u32Size = pstStreamInfo->StrmBufSize;
        pstConfig->u32PhyAddr = pstStreamInfo->StreamMMZBuf.u32StartPhyAddr  + VEDU_MMZ_ALIGN;
        pstConfig->pu8KnlVirAddr = pstStreamInfo->StreamMMZBuf.pu8StartVirAddr + VEDU_MMZ_ALIGN;
        pstConfig->u32ParaSetPhyAddr = pstStreamInfo->SliceBuf.u32StartPhyAddr;
        pstConfig->pu8ParaSetKnlVirAddr = pstStreamInfo->SliceBuf.pu8StartVirAddr;
        pstConfig->u32RsvByte        = 64;
    }
    else if (hStrmMng == STRM_MODE_RECYCLE)
    {
        pstConfig->u32Size = pstStreamInfo->StrmBufSize;
        pstConfig->u32PhyAddr = pstStreamInfo->StreamMMZBuf.u32StartPhyAddr  + VEDU_MMZ_ALIGN;
        pstConfig->pu8KnlVirAddr     = pstStreamInfo->StreamMMZBuf.pu8StartVirAddr + VEDU_MMZ_ALIGN;
        pstConfig->u32Size           =  pstStreamInfo->StrmBufSize;
        pstConfig->u32RsvByte        = 64;
    }

    return HI_SUCCESS;
}

HI_S32 STRM_Create(HI_HANDLE *phHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;
    STRMMNG_INST_CONFIG_S stConfig;

    if ((phHandle == HI_NULL) || (pstStreamInfo == HI_NULL))
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    memset(&stConfig, 0, sizeof(STRMMNG_INST_CONFIG_S));

    if (FindStreamBufferFunc(*phHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    GetConfigInfo(StrmMode, pstStreamInfo, &stConfig);

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_Create == HI_NULL)
    {
        HI_ERR_VENC("Get Stream_Create Function Ptr Is Failure!\n");

        Ret = HI_ERR_VENC_NULL_PTR;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_Create(&PrivateID, &stConfig);
    }

    *phHandle = *phHandle + PrivateID;

    return Ret;
}

HI_S32 STRM_Destroy(HI_U32 hHandle)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_Destroy == HI_NULL)
    {
        HI_ERR_VENC("Get Stream_Destroy Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_Destroy(PrivateID);
    }

    return Ret;
}

HI_S32 STRM_GetWriteBuffer(HI_U32 hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if ((pstInputInfo == HI_NULL) || (pstStreamInfo == HI_NULL))
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_GetWriteBuffer == HI_NULL)
    {
        HI_ERR_VENC("Get Stream_GetWriteBufferFrame Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_GetWriteBuffer(PrivateID, pstInputInfo, pstStreamInfo);
    }

    return Ret;
}

HI_S32 STRM_PutBufferForRecode(HI_U32 hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if ((pstInputInfo == HI_NULL) || (pstStreamInfo == HI_NULL))
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_PutBufferForRecode == NULL)
    {
        HI_ERR_VENC("Get Stream_PutBufferForRecode Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_PutBufferForRecode(PrivateID, pstInputInfo, pstStreamInfo);
    }

    return Ret;
}

HI_S32 STRM_PutWriteBuffer(HI_U32 hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if ((pstInputInfo == HI_NULL) || (pstStreamInfo == HI_NULL))
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_PutWriteBuffer == NULL)
    {
        HI_ERR_VENC("Get Stream_PutFrameWriteBuffer Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_PutWriteBuffer(PrivateID, pstInputInfo, pstStreamInfo);
    }

    return Ret;
}

HI_S32 STRM_AcqReadBuffer(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S *pstVeduPacket)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if ((pstVeduPacket == HI_NULL) || (pstStreamInfo == HI_NULL))
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_AcqReadBuffer == NULL)
    {
        HI_ERR_VENC("Get Stream_AcqReadBuffer Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_AcqReadBuffer(PrivateID, pstStreamInfo, pstVeduPacket);
    }

    return Ret;
}

HI_S32 STRM_RlsReadBuffer(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S *pstVeduPacket)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if ((pstVeduPacket == HI_NULL) || (pstStreamInfo == HI_NULL))
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_RlsReadBuffer == NULL)
    {
        HI_ERR_VENC("Get Stream_RlsReadBuffer Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_RlsReadBuffer(PrivateID, pstStreamInfo, pstVeduPacket);
    }

    return Ret;
}

HI_S32 STRM_GetAcquireStreamInfo(HI_HANDLE hHandle, HI_U32 Protocol, HI_U8* StartVirAddr, VeduEfl_NALU_S *pstVeduPacket,
                                  VENC_STREAM_S* pstStream, VENC_BUF_OFFSET_S *pstBufOffSet)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if ((pstVeduPacket == HI_NULL) || (pstStream == HI_NULL) || (StartVirAddr == HI_NULL) || (pstBufOffSet == HI_NULL))
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_GetAcqStreamInfo == NULL)
    {
        HI_ERR_VENC("Get Stream_GetAcquireStreamInfo Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_GetAcqStreamInfo(PrivateID, Protocol, StartVirAddr, pstVeduPacket, pstStream, pstBufOffSet);
    }

    return Ret;
}

HI_S32 STRM_GetRleaseStreamInfo(HI_HANDLE hHandle, HI_U32 Protocol, STRMMNG_STREAM_INFO_S *pstStreamInfo,
                                 VENC_INFO_ACQUIRE_STREAM_S* pstAcqStrm, VeduEfl_NALU_S* pstVeduPacket)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if ((pstVeduPacket == HI_NULL) || (pstStreamInfo == HI_NULL) || (pstAcqStrm == HI_NULL))
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_GetRlsBufferInfo == NULL)
    {
        HI_ERR_VENC("Get Stream_GetRleaseStreamInfo Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_GetRlsBufferInfo(PrivateID, Protocol, pstStreamInfo, pstAcqStrm, pstVeduPacket);
    }

    return Ret;
}

HI_S32 STRM_GetRleaseStreamInfoIntar(HI_HANDLE hHandle, VENC_STREAM_S *pstStream, VeduEfl_NALU_S* pstVeduPacket)
{
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if ((pstVeduPacket == HI_NULL) || (pstStream == HI_NULL))
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_GetRlsBufferInfoIntar == NULL)
    {
        HI_ERR_VENC("Get Stream_GetRleaseStreamInfoIntar Function Ptr Is Failure!\n");
    }
    else
    {
        g_venc_strm_fun_ptr[StrmMode].pfun_STRM_GetRlsBufferInfoIntar(PrivateID, pstStream, pstVeduPacket);
    }

    return HI_SUCCESS;
}


HI_S32 STRM_CheckBufferSize(HI_HANDLE hHandle, HI_U32 StrmBufSize, HI_U32 CurStrmBufSize)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_CheckBufferSize == NULL)
    {
        HI_ERR_VENC("Get Stream_CheckBufferSize Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_CheckBufferSize(PrivateID, StrmBufSize, CurStrmBufSize);
    }

    return Ret;
}

HI_U32 STRM_CalSlcSize(HI_HANDLE hHandle, HI_U32 Protocol, HI_U32 PicHeight, HI_U32 UnfSplitSize)
{
    HI_U32 SlcSize = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        SlcSize = 0xffffffff;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_CalSlcSize == NULL)
    {
        HI_ERR_VENC("Get Stream_CalSlcSize Function Ptr Is Failure!\n");

        SlcSize = 0xffffffff;
    }
    else
    {
        SlcSize = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_CalSlcSize(PrivateID, Protocol, PicHeight, UnfSplitSize);
    }

    return SlcSize;
}

HI_S32 STRM_GetStrmState(HI_HANDLE hHandle, STRMMNG_State_S* pStrmStatInfo)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if (pStrmStatInfo == HI_NULL)
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_GetStrmState == NULL)
    {
        HI_ERR_VENC("Get Stream_GetStrmNodeState Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_GetStrmState(PrivateID, pStrmStatInfo);
    }

    return Ret;
}

HI_U32 STRM_GetWrittenLength(HI_HANDLE hHandle)
{
    HI_S32 WriteLen = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        WriteLen = 0;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_GetWrittenLen == NULL)
    {
        HI_ERR_VENC("Get Stream_GetWrittenLen Function Ptr Is Failure!\n");
        WriteLen = 0;
    }
    else
    {
        WriteLen = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_GetWrittenLen(PrivateID);
    }

    return WriteLen;
}

HI_S32 STRM_ResetBuffer(HANDLE hHandle, HI_U32 Protocol)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_ResetBuffer == NULL)
    {
        HI_ERR_VENC("Get Stream_ResetBuffer Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }

    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_ResetBuffer(PrivateID, Protocol);
    }

    return Ret;
}

HI_U32 STRM_GetBitBufSize(HANDLE hHandle, HI_U32 *pStrmBufSize, HI_U32 SlcSplitEn, HI_U32 LumaSize)
{
    HI_S32 BitBufSize = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        BitBufSize = 0;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_GetBitBufSize == NULL)
    {
        HI_ERR_VENC("Get Stream_GetBitBufSize Function Ptr Is Failure!\n");
        BitBufSize = 0;
    }
    else
    {
        *pStrmBufSize = D_VENC_ALIGN_UP(*pStrmBufSize, VEDU_MMZ_ALIGN);

        BitBufSize = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_GetBitBufSize(PrivateID, *pStrmBufSize, SlcSplitEn, LumaSize);
    }

    return BitBufSize;
}

HI_S32 STRM_AllocStreamBuf(HANDLE hHandle, VENC_BUFFER_S *pStreamMMZBuf, HI_U32 Protocol, HI_U32 BitBufSize, HI_U32 LumaSize)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if (pStreamMMZBuf == HI_NULL)
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_AllocStreamBuf == NULL)
    {
        HI_ERR_VENC("Get Stream_AllocStreamBuf Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_AllocStreamBuf(PrivateID, pStreamMMZBuf, Protocol, BitBufSize, LumaSize);
    }

    return Ret;
}

HI_S32 STRM_RlsStreamBuf(HANDLE hHandle, VENC_BUFFER_S *pStreamMMZBuf, HI_U32 Protocol)
{
    if (pStreamMMZBuf == HI_NULL)
    {
        return HI_ERR_VENC_NULL_PTR;
    }

#ifdef VENC_SUPPORT_JPGE
    if (Protocol == VEDU_JPGE)
    {
        HI_DRV_VENC_MMZ_UnmapAndRelease(pStreamMMZBuf);
    }
    else
#endif
    {
        HI_DRV_VENC_UnmapAndRelease(pStreamMMZBuf);
    }

    return HI_SUCCESS;
}

HI_S32 STRM_AllocWriteReadPtrBuf(HANDLE hHandle, VENC_BUFFER_S* pWpRpMMZBuf)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 BitBufSize = 4096;

    if (pWpRpMMZBuf == HI_NULL)
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    s32Ret = HI_DRV_VENC_MMZ_AllocAndMap("VENC_WpRpPtrBuf", HI_NULL, BitBufSize, 64, pWpRpMMZBuf);

    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("WpRpPtrBuf HI_DRV_VENC_AllocAndMap failed\n");
    }

    return s32Ret;
}

HI_S32 STRM_RlsWriteReadPtrBuf(HANDLE hHandle, VENC_BUFFER_S* pWpRpMMZBuf)
{
    if (pWpRpMMZBuf == HI_NULL)
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    HI_DRV_VENC_MMZ_UnmapAndRelease(pWpRpMMZBuf);

    return HI_SUCCESS;
}

HI_S32 STRM_AllocParaSetBufAddr(HANDLE hHandle, VENC_BUFFER_S *pParaSetBuf, HI_U32 *pParaSetADDR)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if ((pParaSetBuf == HI_NULL) || (pParaSetADDR == HI_NULL))
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_AllocParaSetBufAddr == NULL)
    {
        HI_ERR_VENC("Get Stream_AllocParaSetBufAddr Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_AllocParaSetBufAddr(PrivateID, pParaSetBuf, pParaSetADDR);
    }

    return Ret;
}

HI_S32 STRM_RlsParaSetBufAddr(HANDLE hHandle, VENC_BUFFER_S *pParaSetBuf)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if (pParaSetBuf == HI_NULL)
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if ((StrmMode == 0) && (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_RlsParaSetBufAddr == NULL))
    {
        HI_ERR_VENC("Get Stream_RlsParaSetBufAddr Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_RlsParaSetBufAddr(PrivateID, pParaSetBuf);
    }

    return Ret;
}

#ifdef VENC_SUPPORT_JPGE
HI_S32 STRM_JPGEWriteHeader(HANDLE hHandle, STRMMNG_INPUT_INFO_S* pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if ((pstInputInfo == HI_NULL) || (pstStreamInfo == HI_NULL))
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_JPGEWriteHeader == NULL)
    {
        HI_ERR_VENC("Get Stream_JPGEWriteHeader Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_JPGEWriteHeader(PrivateID, pstInputInfo, pstStreamInfo);
    }

    return Ret;
}

HI_S32 STRM_PutJPGEWriteBuffer(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if ((pstInputInfo == HI_NULL) || (pstStreamInfo == HI_NULL))
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_PutJPGEWriteBuffer == NULL)
    {
        HI_ERR_VENC("Get Stream_PutJPGEWriteBuffer Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_PutJPGEWriteBuffer(PrivateID, pstInputInfo, pstStreamInfo);
    }

    return Ret;
}

HI_S32 STRM_JPGERemoveHeader(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if ((pstInputInfo == HI_NULL) || (pstStreamInfo == HI_NULL))
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_JPGERemoveHeader == NULL)
    {
        HI_ERR_VENC("Get Stream_JPGERemoveHeader Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_JPGERemoveHeader(PrivateID, pstInputInfo, pstStreamInfo);
    }

    return Ret;
}

HI_S32 STRM_GetJpgeStream(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S *pstVeduPacket, VENC_STREAM_S *pstStream, VENC_BUF_OFFSET_S *pstBufOffSet)
{
    HI_S32 Ret = 0;
    HI_U32 StrmMode  = 0;
    HI_U32 PrivateID = 0;

    if ((pstVeduPacket == HI_NULL) || (pstStreamInfo == HI_NULL) || (pstStream == HI_NULL) || (pstBufOffSet == HI_NULL))
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    if (FindStreamBufferFunc(hHandle, &StrmMode, &PrivateID) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (g_venc_strm_fun_ptr[StrmMode].pfun_STRM_GetJpgeStream == NULL)
    {
        HI_ERR_VENC("Get Stream_GetJpgeStream Function Ptr Is Failure!\n");

        Ret = HI_FAILURE;
    }
    else
    {
        Ret = g_venc_strm_fun_ptr[StrmMode].pfun_STRM_GetJpgeStream(PrivateID, pstStreamInfo, pstVeduPacket, pstStream, pstBufOffSet);
    }

    return Ret;
}

#endif

HI_UNF_HEVCE_NALU_TYPE_E TransNaluTypeNumForH265(HI_U32 NaluType)
{
    HI_UNF_HEVCE_NALU_TYPE_E  enHEVCEType;

    switch (NaluType)
    {
        case H265_NALU_TYPE_P:
            enHEVCEType = HI_UNF_HEVCE_NALU_PSLICE;
            break;

        case H265_NALU_TYPE_IDR:
            enHEVCEType = HI_UNF_HEVCE_NALU_ISLICE;
            break;

        case H265_NALU_TYPE_VPS:
            enHEVCEType = HI_UNF_HEVCE_NALU_VPS;
            break;

        case H265_NALU_TYPE_SPS:
            enHEVCEType = HI_UNF_HEVCE_NALU_SPS;
            break;

        case H265_NALU_TYPE_PPS:
            enHEVCEType = HI_UNF_HEVCE_NALU_PPS;
            break;

        case H265_NALU_TYPE_SEI:
            enHEVCEType = HI_UNF_HEVCE_NALU_SEI;
            break;

        default:
            enHEVCEType = HI_UNF_HEVCE_NALU_BUTT;
            break;
    }

    return enHEVCEType;
}

HI_U32 InverseTransNaluTypeNumForH265(HI_UNF_HEVCE_NALU_TYPE_E enHEVCEType)
{
    HI_U32  NaluType = 0;

    switch (enHEVCEType)
    {
        case HI_UNF_HEVCE_NALU_PSLICE:
            NaluType = H265_NALU_TYPE_P;
            break;

        case HI_UNF_HEVCE_NALU_ISLICE:
            NaluType = H265_NALU_TYPE_IDR;
            break;

        case HI_UNF_HEVCE_NALU_VPS:
            NaluType = H265_NALU_TYPE_VPS;
            break;

        case HI_UNF_HEVCE_NALU_SPS:
            NaluType = H265_NALU_TYPE_SPS;
            break;

        case HI_UNF_HEVCE_NALU_PPS:
            NaluType = H265_NALU_TYPE_PPS;
            break;

        case HI_UNF_HEVCE_NALU_SEI:
            NaluType = H265_NALU_TYPE_SEI;
            break;

        default:
            NaluType = 0;
            break;
    }

    return NaluType;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

