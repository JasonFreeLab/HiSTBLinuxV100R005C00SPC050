/******************************************************************************

  Copyright (C), 2014-2015, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : rawplay.c
  Version       : Initial Draft
  Description   : video raw data player, multi channel support
  History       :
  1.Date        : 2014/11/13
    Author      : y00226912
    Modification: Created file

******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#include <assert.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_demux.h"
#include "hi_adp_mpi.h"
#include "hi_adp_hdmi.h"
#include "hi_common.h"

#ifdef HI_TEE_SUPPORT
#include "tee_client_api.h"
#include "mpi_mmz.h"
#ifndef HI_SMMU_SUPPORT
#include "sec_mmz.h"
#endif
#endif

#ifdef CONFIG_SUPPORT_CA_RELEASE
#define sample_printf
#else
#define sample_printf printf
#endif

#define MAX_CODEC_NUM         (16)

#define MAX_LOAD_TIDX_NUM     (50*1024)       /*一次性从.tidx文件中读取的帧信息数*/

static HI_U32 g_RectWinTable[MAX_CODEC_NUM][3] =
{
    {1, 1, 1},  {2, 2, 1},  {3, 2, 2},  {4, 2, 2},
    {5, 3, 2},  {6, 3, 2},  {7, 3, 3},  {8, 3, 3},
    {9, 3, 3},  {10, 4, 3}, {11, 4, 3}, {12, 4, 3},
    {13, 4, 4}, {14, 4, 4}, {15, 4, 4}, {16, 4, 4},
};

typedef enum
{
    VIDEO_MODE_RANDOM = 0,     /*send by random size*/
    VIDEO_MODE_STRM_SIZE,      /*send by stream info size*/
    VIDEO_MODE_EXT_SIZE,       /*send by external info size*/
    VIDEO_MODE_BUTT
}STREAM_MODE_E;

/*图像帧信息*/
typedef struct
{
    HI_U32 s32FrameNum;
    HI_U32 s32Frameoffset;
    HI_U32 s32FrameSize;
    HI_U32 FrameType;              // frame coding type
    HI_U32 TopFieldType;           // top field coding type
    HI_U32 BtmFieldType;           // buttom field coding type
    long   FramePts;
    HI_U32 FrameStructure;         // 0-frame ; 1-fieldpair
    HI_U32 TopFieldCrc;
    HI_U32 BtmFieldCrc;
    HI_U32 s32FrameCrc;
    HI_U32 NVOPFlag;               // NVOP输不输出的标志
    HI_U32 AlreadyOutPutFlag;      // 帧已经输出标志

}FRAME_INFO_S;

typedef struct
{
    HI_U32 SendCnt;
    FILE *pTidxFile;
    FRAME_INFO_S stFrameInfotidx[MAX_LOAD_TIDX_NUM];

}TIDX_CONTEXT_S;

typedef struct hiCODEC_PARAM_S
{
    HI_BOOL bVidPlay;
    HI_BOOL bTVPEnable;
    HI_BOOL bRandErrEnable;
    STREAM_MODE_E eStreamMode;
    FILE   *pVidEsFile;
    pthread_t EsThread;
    HI_UNF_VCODEC_TYPE_E VdecType;
    HI_BOOL bAdvancedProfile;
    HI_BOOL bCRCEnable;
    HI_U32  CodecVersion;
    HI_HANDLE hAvplay;
    HI_HANDLE hWin;
    HI_MMZ_BUF_S TidxBuffer;
    TIDX_CONTEXT_S *pstContext;

}CODEC_PARAM_S;


CODEC_PARAM_S g_stCodec[MAX_CODEC_NUM];

#define FIXED_FRAME_SIZE          (0x200000)
#define CONFIG_ES_BUFFER_SIZE     (16*1024*1024)

static HI_BOOL g_StopThread = HI_FALSE;
static HI_BOOL g_PlayOnce = HI_FALSE;
static HI_BOOL g_InquireOff = HI_FALSE;
static HI_BOOL g_AutoCrcEnable = HI_FALSE;
static HI_BOOL g_NeedParseHeader = HI_TRUE;
static HI_BOOL g_EsThreadExit = HI_FALSE;

#ifdef HI_TEE_SUPPORT
typedef enum
{
    CMD_TZ_EMPTY_DRM_INITIALIZE = 1,
    CMD_TZ_EMPTY_DRM_TERMINATE,
    CMD_TZ_EMPTY_DRM_CA2TA,
}Hi_TzEmptyDrmCommandId_E;

#ifdef HI_SMMU_SUPPORT
static TEEC_Context   g_TeeContext;
#endif

static TEEC_Session   g_teeSession;

HI_S32 InitSecEnvironment(HI_VOID)
{
#ifdef HI_SMMU_SUPPORT
    TEEC_Result result;
    uint32_t origin;
    TEEC_UUID svc_id = {0x79b77788, 0x9789, 0x4a7a, {0xa2, 0xbe, 0xb6, 0x01, 0x55, 0x11, 0x11, 0x11}};

    TEEC_Operation session_operation;

    memset(&session_operation, 0, sizeof(TEEC_Operation));

    session_operation.started = 1;
    session_operation.paramTypes = TEEC_PARAM_TYPES(
                               TEEC_NONE,
                               TEEC_NONE,
                               TEEC_MEMREF_TEMP_INPUT,
                               TEEC_MEMREF_TEMP_INPUT);

    if (TEEC_InitializeContext(HI_NULL, &g_TeeContext) != TEEC_SUCCESS)
    {
        sample_printf("TEEC_InitializeContext Failed!\n");
        return HI_FAILURE;
    }

    result = TEEC_OpenSession(&g_TeeContext, &g_teeSession, &svc_id, TEEC_LOGIN_IDENTIFY, HI_NULL, &session_operation, &origin);
    if (result != TEEC_SUCCESS)
    {
        sample_printf("TEEC_OpenSession Failed!\n");
        TEEC_FinalizeContext(&g_TeeContext);
        return HI_FAILURE;
    }

    memset(&session_operation, 0, sizeof(TEEC_Operation));

    session_operation.started = 1;
    session_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    result = TEEC_InvokeCommand(&g_teeSession, CMD_TZ_EMPTY_DRM_INITIALIZE, &session_operation, HI_NULL);
    if (TEEC_SUCCESS != result)
    {
        sample_printf("init empty drm failed\n");

        TEEC_CloseSession(&g_teeSession);
        TEEC_FinalizeContext(&g_TeeContext);

        return HI_FAILURE;
    }

    return HI_SUCCESS;

#else
    HI_SEC_MMZ_Init();

    return HI_SUCCESS;
#endif
}


HI_VOID DeInitSecEnvironment(HI_VOID)
{
#ifdef HI_SMMU_SUPPORT
    TEEC_Result result;
    TEEC_Operation session_operation;

    memset(&session_operation, 0, sizeof(TEEC_Operation));

    session_operation.started = 1;
    session_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    result = TEEC_InvokeCommand(&g_teeSession, CMD_TZ_EMPTY_DRM_TERMINATE, &session_operation, HI_NULL);
    if (result != TEEC_SUCCESS)
    {
        sample_printf("deinit empty drm failed\n");
    }

    TEEC_CloseSession(&g_teeSession);

    TEEC_FinalizeContext(&g_TeeContext);
#else
    HI_SEC_MMZ_DeInit();
#endif
}

HI_S32 HI_SEC_CA2TA(HI_U32 SrcAddr, HI_U32 DstAddr, HI_U32 Readlen)
{
    TEEC_Result result;
    TEEC_Operation operation;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE);
    operation.params[0].value.a = (HI_U32)SrcAddr;
    operation.params[0].value.b = Readlen;
    operation.params[1].value.a = (HI_U32)DstAddr;
    operation.params[1].value.b = TEEC_VALUE_UNDEF;

    result = TEEC_InvokeCommand(&g_teeSession, CMD_TZ_EMPTY_DRM_CA2TA, &operation, HI_NULL);
    if (TEEC_SUCCESS != result)
    {
        sample_printf("%s failed, SrcAddr 0x%x, DstAddr 0x%x, Readlen 0x%x\n", __func__, SrcAddr, DstAddr, Readlen);
        return HI_FAILURE;
    }

    return HI_SUCCESS; //(operation.params[1].value.b == 0) ? HI_SUCCESS : HI_FAILURE;
}
#endif

int FrameTypeChartoSINT32(char type)
{
    int FrameType;

    if(type == 'I')
    {
        FrameType = 0;    // 0 表示帧的类型为 I
    }
    else if(type == 'P')
    {
        FrameType = 1;    // 1 表示帧的类型为 P
    }
    else if(type == 'B')
    {
        FrameType = 2;    // 2 表示帧的类型为 B
    }
    else
    {
        FrameType = -1;
    }
    return FrameType;
}

/***********************************************************/
/*              复位存放理论输出帧信息数组                 */
/***********************************************************/
void ResetFrameInfoTidx(FRAME_INFO_S *pFrameInfo)
{
    int i;

    /*将上次文件信息中的信息清空*/
    for(i = 0 ; i < MAX_LOAD_TIDX_NUM ; i++)
    {
        memset(&(pFrameInfo[i]) , -1 , sizeof(FRAME_INFO_S));
    }
}

/***********************************************************/
/*             从.tidx文件中读取一组帧信息                 */
/***********************************************************/
HI_S32 ReadFrameTidxInfo(TIDX_CONTEXT_S *pstContext)
{
    HI_U32 i;
    HI_CHAR *pFrameInfoBuf,*pFrameInfo;
    HI_CHAR Type;
    HI_CHAR FieldType[2];

    ResetFrameInfoTidx(pstContext->stFrameInfotidx);

    if (pstContext->pTidxFile == HI_NULL)
    {
        return HI_FAILURE;
    }

    if(!feof(pstContext->pTidxFile))
    {
        pFrameInfoBuf = (char *)malloc(1024);

        for(i = 0 ; i < MAX_LOAD_TIDX_NUM ; i++)
        {
            fgets(pFrameInfoBuf, 1024, pstContext->pTidxFile);

            pFrameInfo = pFrameInfoBuf;
            sscanf(pFrameInfo, "%d", &(pstContext->stFrameInfotidx[i].s32FrameNum));
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
            sscanf(pFrameInfo, "%x", &(pstContext->stFrameInfotidx[i].s32Frameoffset));
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
            sscanf(pFrameInfo, "%d", &(pstContext->stFrameInfotidx[i].s32FrameSize));
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
            sscanf(pFrameInfo,"%ld", (long *)&(pstContext->stFrameInfotidx[i].FramePts));
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
            sscanf(pFrameInfo,"%c", &Type);
            pstContext->stFrameInfotidx[i].FrameType = FrameTypeChartoSINT32(Type);
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
            sscanf(pFrameInfo,"%x", &(pstContext->stFrameInfotidx[i].FrameStructure));
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
            sscanf(pFrameInfo,"%s", FieldType);
            pstContext->stFrameInfotidx[i].TopFieldType = FrameTypeChartoSINT32(FieldType[0]);
            pstContext->stFrameInfotidx[i].BtmFieldType = FrameTypeChartoSINT32(FieldType[1]);
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
            sscanf(pFrameInfo,"%x", &(pstContext->stFrameInfotidx[i].TopFieldCrc));
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
            sscanf(pFrameInfo,"%x", &(pstContext->stFrameInfotidx[i].BtmFieldCrc));
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
            sscanf(pFrameInfo,"%d", &(pstContext->stFrameInfotidx[i].NVOPFlag));

            if( feof(pstContext->pTidxFile))
            {
                break;
            }
        }

        free(pFrameInfoBuf);
    }
    return HI_SUCCESS;
}

int is_framepacket_standard(HI_UNF_VCODEC_TYPE_E format)
{
    if( HI_UNF_VCODEC_TYPE_H263     == format
     || HI_UNF_VCODEC_TYPE_DIVX3    == format
     || HI_UNF_VCODEC_TYPE_VP8      == format
     || HI_UNF_VCODEC_TYPE_VP6      == format
     || HI_UNF_VCODEC_TYPE_VP6F     == format
     || HI_UNF_VCODEC_TYPE_VP6A     == format
     || HI_UNF_VCODEC_TYPE_SORENSON == format
     || HI_UNF_VCODEC_TYPE_REAL8    == format
     || HI_UNF_VCODEC_TYPE_REAL9    == format
     || HI_UNF_VCODEC_TYPE_VP9      == format )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

HI_S32 TryOpenTidxFile(TIDX_CONTEXT_S *pCtx, HI_CHAR *pSrcFile)
{
    HI_S32 Ret;
    HI_CHAR TidxFile[512];

    snprintf(TidxFile, sizeof(TidxFile), "%s.tidx", pSrcFile);

    pCtx->pTidxFile = fopen(TidxFile, "r");
    if (pCtx->pTidxFile == HI_NULL)
    {
        return HI_FAILURE;
    }

    Ret = ReadFrameTidxInfo(pCtx);
    fclose(pCtx->pTidxFile);

    return Ret;
}

HI_S32 ParseFrameSizeFromExtInfo(CODEC_PARAM_S *pCodec, HI_U32 *pFrameSize)
{
    HI_U32 ReadFrameSize = 0;
    HI_U32 FrameOffset = 0;
    TIDX_CONTEXT_S *pCtx = pCodec->pstContext;

    if (pCtx->SendCnt > 0 && pCtx->stFrameInfotidx[pCtx->SendCnt].s32FrameNum <= 0)
    {
       sample_printf("Frame[%d] FrameNum(%d) in FrameInfo invalid, stream send over!\n", pCtx->SendCnt, pCtx->stFrameInfotidx[pCtx->SendCnt].s32FrameNum);
       return HI_FAILURE;
    }

    if (pCtx->stFrameInfotidx[pCtx->SendCnt].s32FrameSize != 0)
    {
       ReadFrameSize = pCtx->stFrameInfotidx[pCtx->SendCnt].s32FrameSize;
    }

    FrameOffset = pCtx->stFrameInfotidx[pCtx->SendCnt].s32Frameoffset;
    if (FrameOffset != 0)
    {
       fseek(pCodec->pVidEsFile, FrameOffset, 0);
    }

    *pFrameSize = ReadFrameSize;
    if (*pFrameSize == 0 || *pFrameSize > FIXED_FRAME_SIZE)
    {
        sample_printf("%s parse frame size exceed %d\n", __func__, FIXED_FRAME_SIZE);
        return HI_FAILURE;
    }

    pCtx->SendCnt++;

    return HI_SUCCESS;
}

HI_S32 InquireStatus(HI_HANDLE hAvplay)
{
    HI_S32    ret;
    static HI_U32 InquireCount = 0;
    static HI_U32 FrameCountRec = 0;
    HI_U32 FrameCountRead = 0;
    HI_UNF_AVPLAY_STATUS_INFO_S stStatusInfo;

#define MAX_INQUIRE_COUNT (1000)

    ret = HI_UNF_AVPLAY_GetStatusInfo(hAvplay, &stStatusInfo);
    if (ret == HI_FAILURE)
    {
        return HI_FAILURE;
    }

    FrameCountRead = stStatusInfo.u32VidFrameCount;
    if (FrameCountRead != FrameCountRec)
    {
        InquireCount = 0;
        FrameCountRec = FrameCountRead;
        return HI_SUCCESS;
    }

    InquireCount++;
    if (InquireCount > MAX_INQUIRE_COUNT)
    {
        sample_printf("[Error]:InquireCount > %d\n", MAX_INQUIRE_COUNT);
        return HI_FAILURE;
    }

    if (g_InquireOff == HI_TRUE)
    {
        sample_printf("close inquire\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_VOID NotifyEOS(HI_HANDLE hAvplay)
{
    HI_S32 Ret = HI_FAILURE;
    HI_BOOL bIsEmpty = HI_FALSE;
    HI_UNF_AVPLAY_FLUSH_STREAM_OPT_S stFlushOpt;

    sample_printf("Sample send stream finish.\n");

    HI_UNF_AVPLAY_FlushStream(hAvplay, &stFlushOpt);
    do
    {
        Ret = HI_UNF_AVPLAY_IsBuffEmpty(hAvplay, &bIsEmpty);
        if (Ret != HI_SUCCESS)
        {
            sample_printf("call HI_UNF_AVPLAY_IsBuffEmpty failed.\n");
            break;
        }

        usleep(10*1000);
        if (InquireStatus(hAvplay) != HI_SUCCESS)
        {
            break;
        }
    }while(bIsEmpty != HI_TRUE);

    sleep(1);
    return;
}

HI_S32 ParseVP9FrameSize(CODEC_PARAM_S *pCodec, HI_U32 *pFrameSize)
{
    HI_CHAR Vp9FileHdr[32];
    HI_CHAR Vp9FrmHdr[12];
    char *const g_IVFSignature = "DKIF";
    static HI_U32 FrameCnt = 0;

    if (g_NeedParseHeader == HI_TRUE)
    {
        if (fread(Vp9FileHdr, 1, 32, pCodec->pVidEsFile) != 32)
        {
            sample_printf("Read vp9 file header failed.\n");

            return HI_FAILURE;
        }

        if (memcmp(g_IVFSignature, Vp9FileHdr, 4) != 0)
        {
            sample_printf("This VP9 file is not IVF file (Format ERROR).\n");

            return HI_FAILURE;
        }

        g_NeedParseHeader = HI_FALSE;
        FrameCnt = 0;
    }

    if (fread(Vp9FrmHdr, 1, 12, pCodec->pVidEsFile) != 12)
    {
        sample_printf("No enough stream to parse frame size!\n");

        return HI_FAILURE;
    }

    *pFrameSize  = Vp9FrmHdr[3] << 24;
    *pFrameSize |= Vp9FrmHdr[2] << 16;
    *pFrameSize |= Vp9FrmHdr[1] << 8;
    *pFrameSize |= Vp9FrmHdr[0];

    //sample_printf("Parse frame %d size %d, (%d %d %d %d)\n", FrameCnt, *pFrameSize, Vp9FrmHdr[3], Vp9FrmHdr[2], Vp9FrmHdr[1], Vp9FrmHdr[0]);
    FrameCnt++;

    if (*pFrameSize == 0 || *pFrameSize > FIXED_FRAME_SIZE)
    {
        sample_printf("Parse frame size %d exceed %d\n", *pFrameSize, FIXED_FRAME_SIZE);

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 ParseOtherFrameSize(CODEC_PARAM_S *pCodec, HI_U32 *pFrameSize)
{
    HI_U32 Readlen = 0;

    Readlen = fread(pFrameSize, 1, 4, pCodec->pVidEsFile);
    if (Readlen != 4)
    {
        sample_printf("%s parse frame size failed, exit!\n", __func__);

        return HI_FAILURE;
    }

    if (*pFrameSize == 0 || *pFrameSize > FIXED_FRAME_SIZE)
    {
        sample_printf("%s parse frame size exceed %d\n", __func__, FIXED_FRAME_SIZE);

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 ParseFrameSize(CODEC_PARAM_S *pCodec, HI_U32 *pFrameSize)
{
    HI_S32 Ret = HI_SUCCESS;

    if(pCodec->eStreamMode == VIDEO_MODE_EXT_SIZE)
    {
        Ret = ParseFrameSizeFromExtInfo(pCodec, pFrameSize);

    }
    else if (pCodec->eStreamMode == VIDEO_MODE_STRM_SIZE)
    {
        if (pCodec->VdecType == HI_UNF_VCODEC_TYPE_VP9)
        {
            Ret = ParseVP9FrameSize(pCodec, pFrameSize);
        }
        else
        {
            Ret = ParseOtherFrameSize(pCodec, pFrameSize);
        }
    }
    else
    {
        *pFrameSize = FIXED_FRAME_SIZE;
    }

    return Ret;
}

HI_VOID RandomAlterEsData(CODEC_PARAM_S *pCodec, HI_U8 *pEsBuf, HI_U32 EsSize)
{
    HI_U32 pos;
    HI_U32 RandStep = 10;
    HI_U32 RandStart = pEsBuf[EsSize-1]%RandStep;

    for (pos=RandStart; pos<EsSize; pos++)
    {
        if (pos%RandStep == 1)
        {
            pEsBuf[pos] = pEsBuf[pos-1];
        }
    }

    return;
}

HI_VOID EsTthread(HI_VOID *args)
{
    HI_S32 Ret = HI_FAILURE;
    HI_S32 Readlen   = 0;
    HI_U32 FrameSize = 0;
    HI_U8 *pBuffer = HI_NULL;
    CODEC_PARAM_S *pCodec = (CODEC_PARAM_S *)args;
    HI_UNF_STREAM_BUF_S stStreamBuf;
    HI_UNF_AVPLAY_PUTBUFEX_OPT_S stExOpt;
    stExOpt.bContinue = HI_TRUE;
    stExOpt.bEndOfFrm = HI_FALSE;

    if (pCodec->eStreamMode != VIDEO_MODE_RANDOM)
    {
        stExOpt.bEndOfFrm = HI_TRUE;
    }

#ifdef HI_TEE_SUPPORT
    HI_MMZ_BUF_S stCAStreamBuf;
    HI_UNF_AVPLAY_TVP_ATTR_S AvTVPAttr;

    memset(&stCAStreamBuf, 0, sizeof(HI_MMZ_BUF_S));
    memset(&AvTVPAttr, 0, sizeof(HI_UNF_AVPLAY_TVP_ATTR_S));

    HI_UNF_AVPLAY_GetAttr(pCodec->hAvplay, HI_UNF_AVPLAY_ATTR_ID_TVP, &AvTVPAttr);

    if (AvTVPAttr.bEnable == HI_TRUE)
    {
    #ifdef HI_SMMU_SUPPORT
        strncpy(stCAStreamBuf.bufname, "CAStreamBuf", sizeof(stCAStreamBuf.bufname));
        stCAStreamBuf.bufsize = 4*1024*1024;

        stCAStreamBuf.phyaddr = HI_MPI_SMMU_New(stCAStreamBuf.bufname, stCAStreamBuf.bufsize);
        if (stCAStreamBuf.phyaddr != 0)
        {
            stCAStreamBuf.user_viraddr = HI_MPI_SMMU_Map(stCAStreamBuf.phyaddr, HI_FALSE);
            if (stCAStreamBuf.user_viraddr == 0)
            {
                sample_printf("%s: map smmu error phy:0x%x\n", __func__, stCAStreamBuf.phyaddr);

                HI_MPI_SMMU_Delete(stCAStreamBuf.phyaddr);

                return;
            }
        }
        else
        {
            sample_printf("%s: map smmu error size:0x%x\n", __func__, stCAStreamBuf.bufsize);
            return;
        }
    #else
        strncpy(stCAStreamBuf.bufname, "CAStreamBuf", sizeof(stCAStreamBuf.bufname));
                stCAStreamBuf.overflow_threshold  = 100;
                stCAStreamBuf.underflow_threshold = 0;
                stCAStreamBuf.bufsize = FIXED_FRAME_SIZE;
                Ret = HI_MPI_MMZ_Malloc(&stCAStreamBuf);
        if (Ret != HI_SUCCESS)
        {
           sample_printf("Alloc tee temp es buffer %d failed!\n", stCAStreamBuf.bufsize);

           return;
        }

    #endif
    }
#endif

    while (!g_StopThread)
    {
        if (!pCodec->bVidPlay)
        {
            break;
        }

        if (FrameSize == 0)
        {
            Ret = ParseFrameSize(pCodec, &FrameSize);
            if (Ret != HI_SUCCESS)
            {
                goto END_OF_FILE;
            }
            //sample_printf("FrameSize = %d\n", FrameSize);
        }

        Ret = HI_UNF_AVPLAY_GetBuf(pCodec->hAvplay, HI_UNF_AVPLAY_BUF_ID_ES_VID, FrameSize, &stStreamBuf, 0);
        if (Ret != HI_SUCCESS)
        {
            usleep(10*1000);
            if(InquireStatus(pCodec->hAvplay) != HI_SUCCESS)
            {
                break;
            }
            else
            {
                continue;
            }
        }

#ifdef HI_TEE_SUPPORT
        if(HI_TRUE == AvTVPAttr.bEnable)
        {
            pBuffer = (HI_U8 *)stCAStreamBuf.user_viraddr;
        }
        else
#endif
        {
            pBuffer = (HI_U8 *)stStreamBuf.pu8Data;
        }

        Readlen = fread(pBuffer, sizeof(HI_S8), FrameSize, pCodec->pVidEsFile);
        if (Readlen < 0)
        {
            sample_printf("Sample read vid file error!\n");

            goto END_OF_THREAD;
        }
        else if (Readlen == 0)
        {
            goto END_OF_FILE;
        }
        else
        {
            if (pCodec->bRandErrEnable == HI_TRUE)
            {
                RandomAlterEsData(pCodec, pBuffer, Readlen);
            }

        #ifdef HI_TEE_SUPPORT
            if(AvTVPAttr.bEnable == HI_TRUE)
            {
                Ret = HI_SEC_CA2TA((HI_U32)stCAStreamBuf.phyaddr, (HI_U32)(long)stStreamBuf.pu8Data, Readlen);
                if (Ret != HI_SUCCESS)
                {
                    sample_printf("Tee call CA2TA failed!\n");

                    goto END_OF_THREAD;
                }
            }
        #endif

            Ret = HI_UNF_AVPLAY_PutBufEx(pCodec->hAvplay, HI_UNF_AVPLAY_BUF_ID_ES_VID, Readlen, 0, &stExOpt);
            if (Ret != HI_SUCCESS)
            {
                sample_printf("Sample put es buffer failed!\n");

                goto END_OF_THREAD;
            }

            goto END_OF_RUN;
        }

END_OF_FILE:
        if (HI_TRUE == g_PlayOnce)
        {
            NotifyEOS(pCodec->hAvplay);

            goto END_OF_THREAD;
        }
        else
        {
            sample_printf("Sample rewind!\n");
            g_NeedParseHeader = HI_TRUE;

            rewind(pCodec->pVidEsFile);
        }

END_OF_RUN:
        usleep(5 * 1000);
        FrameSize = 0;

        continue;
    }

END_OF_THREAD:
#ifdef HI_TEE_SUPPORT
    if(AvTVPAttr.bEnable == HI_TRUE)
    {
    #ifdef HI_SMMU_SUPPORT
        HI_MPI_SMMU_Unmap(stCAStreamBuf.phyaddr);
        HI_MPI_SMMU_Delete(stCAStreamBuf.phyaddr);
    #else
         HI_MPI_MMZ_Free(&stCAStreamBuf);
    #endif
    }
#endif

    g_EsThreadExit = HI_TRUE;

    return;
}

HI_BOOL IsCrcModeEnable(HI_CHAR *pStr)
{
    HI_BOOL IsCrcMode = HI_FALSE;

    if (pStr == HI_NULL)
    {
        return HI_FALSE;
    }

    if (strstr(pStr, "crc") != HI_NULL)
    {
        IsCrcMode = HI_TRUE;
    }

    if (!strcasecmp("crc_auto", pStr))
    {
        g_AutoCrcEnable = HI_TRUE;
    }

    return IsCrcMode;
}

HI_S32 InitCrcEnvironment(CODEC_PARAM_S *pCodec, HI_CHAR *pCrcMode, HI_CHAR *pSrcFile)
{
    HI_S32 Ret;
    HI_CHAR EchoStr[512];
    HI_MMZ_BUF_S *pTidxBuffer = &(pCodec->TidxBuffer);

    snprintf(pTidxBuffer->bufname, sizeof(pTidxBuffer->bufname), "Sample");
    pTidxBuffer->bufsize = sizeof(TIDX_CONTEXT_S);

    Ret = HI_MMZ_Malloc(pTidxBuffer);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("Alloc buffer %s size %d failed!\n", pTidxBuffer->bufname, pTidxBuffer->bufsize);
        return HI_FAILURE;
    }
    pCodec->pstContext = (TIDX_CONTEXT_S *)(pTidxBuffer->user_viraddr);
    memset(pCodec->pstContext, 0, sizeof(TIDX_CONTEXT_S));

    if (pCodec->VdecType == HI_UNF_VCODEC_TYPE_VP8)
    {
        if (TryOpenTidxFile(pCodec->pstContext, pSrcFile) == HI_SUCCESS)
        {
            pCodec->eStreamMode = VIDEO_MODE_EXT_SIZE;
        }
        else
        {
            sample_printf("Open VP8 TidxFile failed!\n");
            return HI_FAILURE;
        }
    }

    snprintf(EchoStr, sizeof(EchoStr), "echo %s %s > /proc/vfmw/crc", pCrcMode, pSrcFile);
    system(EchoStr);

    system("echo map_frm on > /proc/msp/vdec_ctrl");

    g_PlayOnce = HI_TRUE;

    pCodec->bCRCEnable = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 ExitCrcEnvironment(CODEC_PARAM_S *pCodec)
{
    system("echo map_frm off > /proc/msp/vdec_ctrl");
    system("echo crc_off > /proc/vfmw/crc");
    HI_MMZ_Free(&(pCodec->TidxBuffer));
    pCodec->bCRCEnable = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 GetCodecParam(HI_CHAR *argv[], CODEC_PARAM_S *pCodec, HI_U32 *pUsedNum)
{
    HI_U32 CurPos = 0;
    HI_CHAR *pSrcFile = HI_NULL;

    pSrcFile = argv[CurPos];
    pCodec->pVidEsFile = fopen(pSrcFile, "rb");
    if (pCodec->pVidEsFile == HI_NULL)
    {
        sample_printf("open file %s error!\n", argv[CurPos]);
        return HI_FAILURE;
    }
    CurPos++;

    if (!strcasecmp("mpeg2", argv[CurPos]))
    {
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_MPEG2;
    }
    else if (!strcasecmp("mpeg4", argv[CurPos]))
    {
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_MPEG4;
    }
    else if (!strcasecmp("h263", argv[CurPos]))
    {
        pCodec->eStreamMode = VIDEO_MODE_STRM_SIZE;
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_H263;
    }
    else if (!strcasecmp("sor", argv[CurPos]))
    {
        pCodec->eStreamMode = VIDEO_MODE_STRM_SIZE;
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_SORENSON;
    }
    else if (!strcasecmp("vp6", argv[CurPos]))
    {
        pCodec->eStreamMode = VIDEO_MODE_STRM_SIZE;
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_VP6;
    }
    else if (!strcasecmp("vp6f", argv[CurPos]))
    {
        pCodec->eStreamMode = VIDEO_MODE_STRM_SIZE;
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_VP6F;
    }
    else if (!strcasecmp("vp6a", argv[CurPos]))
    {
        pCodec->eStreamMode = VIDEO_MODE_STRM_SIZE;
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_VP6A;
    }
    else if (!strcasecmp("h264", argv[CurPos]))
    {
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_H264;
    }
	else if (!strcasecmp("h265", argv[CurPos]))
    {
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_HEVC;
    }
    else if (!strcasecmp("mvc", argv[CurPos]))
    {
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_MVC;
    }
    else if (!strcasecmp("avs", argv[CurPos]))
    {
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_AVS;
    }
    else if (!strcasecmp("avs2", argv[CurPos]))
    {
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_AVS2;
    }
    else if (!strcasecmp("real8", argv[CurPos]))
    {
        pCodec->eStreamMode = VIDEO_MODE_STRM_SIZE;
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_REAL8;
    }
    else if (!strcasecmp("real9", argv[CurPos]))
    {
        pCodec->eStreamMode = VIDEO_MODE_STRM_SIZE;
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_REAL9;
    }
    else if (!strcasecmp("vc1ap", argv[CurPos]))
    {
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_VC1;
        pCodec->bAdvancedProfile = 1;
        pCodec->CodecVersion     = 8;
    }
    else if (!strcasecmp("vc1smp5", argv[CurPos]))
    {
        pCodec->eStreamMode = VIDEO_MODE_STRM_SIZE;
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_VC1;
        pCodec->bAdvancedProfile = 0;
        pCodec->CodecVersion     = 5;  //WMV3
    }
    else if (!strcasecmp("vc1smp8", argv[CurPos]))
    {
        pCodec->eStreamMode = VIDEO_MODE_STRM_SIZE;
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_VC1;
        pCodec->bAdvancedProfile = 0;
        pCodec->CodecVersion     = 8;  //not WMV3
    }
    else if (!strcasecmp("vp8", argv[CurPos]))
    {
        pCodec->eStreamMode = VIDEO_MODE_STRM_SIZE;
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_VP8;
    }
    else if (!strcasecmp("vp9", argv[CurPos]))
    {
        pCodec->eStreamMode = VIDEO_MODE_STRM_SIZE;
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_VP9;
    }
    else if (!strcasecmp("divx3", argv[CurPos]))
    {
        pCodec->eStreamMode = VIDEO_MODE_STRM_SIZE;
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_DIVX3;
    }
    else if (!strcasecmp("mvc", argv[CurPos]))
    {
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_MVC;
    }
    else if (!strcasecmp("mjpeg", argv[CurPos]))
    {
        pCodec->eStreamMode = VIDEO_MODE_STRM_SIZE;
        pCodec->VdecType = HI_UNF_VCODEC_TYPE_MJPEG;
    }
    else
    {
        sample_printf("unsupport vid codec type!\n");
        return HI_FAILURE;
    }
    CurPos++;

#ifdef HI_TEE_SUPPORT
    if (argv[CurPos] != HI_NULL)
    {
        if (!strcasecmp("tvpon", argv[CurPos]))
        {
            pCodec->bTVPEnable = HI_TRUE;
            CurPos++;
        }
        else if (!strcasecmp("tvpoff", argv[CurPos]))
        {
            pCodec->bTVPEnable = HI_FALSE;
            CurPos++;
        }
    }
#endif

    if (argv[CurPos] != HI_NULL)
    {
        if (!strcasecmp("randerr", argv[CurPos]))
        {
            pCodec->bRandErrEnable = HI_TRUE;
            CurPos++;
            sample_printf("Enable random error test.\n");
        }
    }

    if (argv[CurPos] != HI_NULL)
    {
        if (IsCrcModeEnable(argv[CurPos]) == HI_TRUE)
        {
            HI_CHAR CrcMode[10];
            strncpy(CrcMode, argv[CurPos], strlen(argv[CurPos])+1);
            CurPos++;

            if (InitCrcEnvironment(pCodec, CrcMode, pSrcFile) != HI_SUCCESS)
            {
                sample_printf("InitCrcEnvironment failed!\n");
                return HI_FAILURE;
            }
        }
    }

    (*pUsedNum) += CurPos;

    return HI_SUCCESS;
}

HI_VOID GetWinParam(HI_U32 TotalWinNum, HI_U32 Index, HI_RECT_S *pRectWin)
{
	HI_U32 AvrWidth, AvrHeight;
    HI_U32 DispWidth, DispHeight;
    HI_U32 AlignXNum, AlignYNum;

    AlignXNum = g_RectWinTable[TotalWinNum-1][1];
    AlignYNum = g_RectWinTable[TotalWinNum-1][2];

    HI_UNF_DISP_GetVirtualScreen(HI_UNF_DISPLAY1, &DispWidth, &DispHeight);

    AvrWidth  = DispWidth/AlignXNum;
    AvrHeight = DispHeight/AlignYNum;

    pRectWin->s32X = (Index%AlignXNum)*AvrWidth;
    pRectWin->s32Y = (Index/AlignXNum)*AvrHeight;;
    pRectWin->s32Width  = AvrWidth;
    pRectWin->s32Height = AvrHeight;

    return;
}

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32  Ret = HI_FAILURE;
    HI_BOOL bHaveTVPInst = HI_FALSE;
    HI_S32  pos, index;
    HI_U32  UsedNum = 0;
    HI_BOOL bLowDelay = HI_FALSE;
    HI_S32  CurCodecNum  = 0;
	HI_S32  s32FrameRate = 0;
    HI_CHAR InputCmd[32];
    HI_UNF_ENC_FMT_E enDefaultFmt = HI_UNF_ENC_FMT_720P_50;
    CODEC_PARAM_S   *pCodec       = HI_NULL;
    HI_RECT_S                     stRectWin;
    HI_UNF_AVPLAY_ATTR_S          stAvplayAttr;
    HI_UNF_SYNC_ATTR_S            stAvSyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S      stStopAttr;
    HI_UNF_VCODEC_ATTR_S          stVcodecAttr;
    HI_UNF_AVPLAY_FRMRATE_PARAM_S stFramerate;
    HI_UNF_AVPLAY_OPEN_OPT_S      stMaxCapbility;
#ifdef HI_TEE_SUPPORT
    HI_UNF_AVPLAY_TVP_ATTR_S      stAvTVPAttr;
#endif

    if (argc < 3)
    {
        printf(" usage: sample_rawplay vfile vtype -[options] \n");
        printf(" vtype: h264/h265/mpeg2/mpeg4/avs/avs2/real8/real9/vc1ap/vc1smp5/vc1smp8/vp6/vp6f/vp6a/vp8/vp9/divx3/h263/sor\n");
        printf(" options:\n"
               " -once,       run one time only \n"
               " -fps 60,     run on on 60 fps \n"
               " -ldy,        run on on lowdelay mode \n"
               " -crc_auto, enable crc auto check mode \n"
               " -crc_manu, enable crc manu check mode \n"
               " -crc_gen,   enable crc gen_crc mode \n"
               " 1080p_50/1080p_60  video output at 1080p_50 or 1080p_60\n");
#ifdef HI_TEE_SUPPORT
        printf(" -tvpon,   turn on tvp only the first channel run on tvp \n");
        printf(" -tvpoff,  turn off tvp \n");
#endif
        printf(" examples: \n");
        printf("   sample_rawplay vfile0 h264 vfile1 h265 ...\n");

        return HI_FAILURE;
    }

    memset(g_stCodec, 0, MAX_CODEC_NUM*sizeof(CODEC_PARAM_S));

    for (index = 0; index < MAX_CODEC_NUM; index++)
    {
        pos = 1 + UsedNum;
        if (pos >= argc-1)
        {
            break;
        }

        Ret = GetCodecParam(&argv[pos], &g_stCodec[index], &UsedNum);
        if (Ret == HI_SUCCESS)
        {
            CurCodecNum++;
            g_stCodec[index].bVidPlay = HI_TRUE;
            if (bHaveTVPInst == HI_FALSE)
            {
                bHaveTVPInst = g_stCodec[index].bTVPEnable;
            }
        }
        else if (0 == CurCodecNum)
        {
            sample_printf("Get Codec param failed!\n");
            return HI_FAILURE;
        }
        else
        {
            break;
        }
    }
    sample_printf("%d source to play.\n", CurCodecNum);

    for (index = 0; index < argc; index++)
    {
        if (!strcasecmp("1080p_50", argv[index]))
        {
            sample_printf("ESPlay use 1080p_50 output\n");
            enDefaultFmt = HI_UNF_ENC_FMT_1080P_50;
            break;
        }
        else if (!strcasecmp("1080p_60", argv[index]))
        {
            sample_printf("ESPlay use 1080p_60 output\n");
            enDefaultFmt = HI_UNF_ENC_FMT_1080P_60;
            break;
        }
        else if (!strcasecmp("-once", argv[index]))
        {
            sample_printf("Play once only.\n");
            g_PlayOnce = HI_TRUE;
        }
        else if (!strcasecmp("-inquire_off", argv[index]))
        {
            sample_printf("InquireStatus off.\n");
            g_InquireOff = HI_TRUE;
        }
        else if (!strcasecmp("-ldy", argv[index]))
        {
            bLowDelay = HI_TRUE;
        }
        else if (!strcasecmp("-fps", argv[index]))
        {
            s32FrameRate = atoi(argv[index+1]);
            if(s32FrameRate < 0)
            {
                sample_printf("Invalid fps.\n");
                return HI_FAILURE;
            }
        }
    }

#ifdef HI_TEE_SUPPORT
    if (bHaveTVPInst == HI_TRUE)
    {
        Ret = InitSecEnvironment();
        if (Ret != HI_SUCCESS)
        {
            sample_printf("call InitSecEnvironment failed.\n");
            goto WIN_DETATCH;
        }
    }
#endif

    HI_SYS_Init();

    HIADP_MCE_Exit();

    Ret = HI_UNF_AVPLAY_Init();
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_AVPLAY_Init failed.\n");
        goto SYS_DEINIT;
    }

    Ret = HIADP_Disp_Init(enDefaultFmt);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call DispInit failed.\n");
        goto AVPLAY_DEINIT;
    }

    Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call DispInit failed.\n");
        goto DISP_DEINIT;
    }

    for (index = 0; index < CurCodecNum; index++)
    {
        pCodec = &g_stCodec[index];
        if (pCodec->bVidPlay)
        {
            Ret  = HI_UNF_AVPLAY_GetDefaultConfig(&stAvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_ES);
            stAvplayAttr.stStreamAttr.u32VidBufSize = CONFIG_ES_BUFFER_SIZE;
            Ret |= HI_UNF_AVPLAY_Create(&stAvplayAttr, &pCodec->hAvplay);
            if (Ret != HI_SUCCESS)
            {
                sample_printf("call HI_UNF_AVPLAY_Create failed.\n");
                goto VO_DEINIT;
            }

            Ret = HI_UNF_AVPLAY_GetAttr(pCodec->hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stAvSyncAttr);
            stAvSyncAttr.enSyncRef = HI_UNF_SYNC_REF_NONE;
            Ret |= HI_UNF_AVPLAY_SetAttr(pCodec->hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stAvSyncAttr);
            if (HI_SUCCESS != Ret)
            {
                sample_printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
                goto AVPLAY_DESTROY;
            }

            GetWinParam(CurCodecNum, index, &stRectWin);
            Ret |= HIADP_VO_CreatWin(&stRectWin, &pCodec->hWin);
            if (Ret != HI_SUCCESS)
            {
                sample_printf("call VoInit failed.\n");
                HIADP_VO_DeInit();
                goto AVPLAY_DESTROY;
            }

            if (HI_UNF_VCODEC_TYPE_MVC == pCodec->VdecType)
            {
                stMaxCapbility.enCapLevel      = HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
                stMaxCapbility.enDecType       = HI_UNF_VCODEC_DEC_TYPE_BUTT;
                stMaxCapbility.enProtocolLevel = HI_UNF_VCODEC_PRTCL_LEVEL_MVC;
            }
            else
            {
                stMaxCapbility.enCapLevel      = HI_UNF_VCODEC_CAP_LEVEL_4096x2160;
                stMaxCapbility.enDecType       = HI_UNF_VCODEC_DEC_TYPE_BUTT;
                stMaxCapbility.enProtocolLevel = HI_UNF_VCODEC_PRTCL_LEVEL_BUTT;
            }

#ifdef HI_TEE_SUPPORT
            stAvTVPAttr.bEnable = pCodec->bTVPEnable;
            Ret = HI_UNF_AVPLAY_SetAttr(pCodec->hAvplay, HI_UNF_AVPLAY_ATTR_ID_TVP, &stAvTVPAttr);
            if (Ret != HI_SUCCESS)
            {
                sample_printf("call HI_UNF_AVPLAY_SetAttr TVP failed.\n");
                goto VO_DESTROY;
            }
#endif
            Ret = HI_UNF_AVPLAY_ChnOpen(pCodec->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &stMaxCapbility);
            if (Ret != HI_SUCCESS)
            {
                sample_printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
                goto VO_DESTROY;
            }

            /*set compress attr*/
            Ret = HI_UNF_AVPLAY_GetAttr(pCodec->hAvplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &stVcodecAttr);

            if (HI_UNF_VCODEC_TYPE_VC1 == pCodec->VdecType)
            {
                stVcodecAttr.unExtAttr.stVC1Attr.bAdvancedProfile = pCodec->bAdvancedProfile;
                stVcodecAttr.unExtAttr.stVC1Attr.u32CodecVersion  = pCodec->CodecVersion;
            }
            else if (HI_UNF_VCODEC_TYPE_VP6 == pCodec->VdecType)
            {
                stVcodecAttr.unExtAttr.stVP6Attr.bReversed = 0;
            }

            stVcodecAttr.enType = pCodec->VdecType;

            Ret |= HI_UNF_AVPLAY_SetAttr(pCodec->hAvplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &stVcodecAttr);
            if (HI_SUCCESS != Ret)
            {
                sample_printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
                goto VCHN_CLOSE;
            }

            Ret = HI_UNF_VO_AttachWindow(pCodec->hWin, pCodec->hAvplay);
            if (Ret != HI_SUCCESS)
            {
                sample_printf("call HI_UNF_VO_AttachWindow failed.\n");
                goto VCHN_CLOSE;
            }

            Ret = HI_UNF_VO_SetWindowEnable(pCodec->hWin, HI_TRUE);
            if (Ret != HI_SUCCESS)
            {
                sample_printf("call HI_UNF_VO_SetWindowEnable failed.\n");
                goto WIN_DETATCH;
            }

            Ret = HIADP_AVPlay_SetVdecAttr(pCodec->hAvplay, pCodec->VdecType, HI_UNF_VCODEC_MODE_NORMAL);
            if (Ret != HI_SUCCESS)
            {
                sample_printf("call HIADP_AVPlay_SetVdecAttr failed.\n");
                goto WIN_DETATCH;
            }

            if (g_AutoCrcEnable == HI_TRUE)
            {
                s32FrameRate = 60;
            }

            if (0 != s32FrameRate)
            {
               stFramerate.enFrmRateType = HI_UNF_AVPLAY_FRMRATE_TYPE_USER;
               stFramerate.stSetFrmRate.u32fpsInteger = s32FrameRate;
               stFramerate.stSetFrmRate.u32fpsDecimal = 0;
               HI_UNF_AVPLAY_SetAttr(pCodec->hAvplay, HI_UNF_AVPLAY_ATTR_ID_FRMRATE_PARAM, &stFramerate);
                if (Ret != HI_SUCCESS)
                {
                    sample_printf("call HIADP_AVPlay_SetVdecAttr failed.\n");
                    goto WIN_DETATCH;
                }
            }

            if (bLowDelay)
            {
                HI_UNF_AVPLAY_LOW_DELAY_ATTR_S stLowdelayAttr;

                HI_UNF_AVPLAY_GetAttr(pCodec->hAvplay, HI_UNF_AVPLAY_ATTR_ID_LOW_DELAY, &stLowdelayAttr);

                stLowdelayAttr.bEnable = HI_TRUE;
                Ret = HI_UNF_AVPLAY_SetAttr(pCodec->hAvplay, HI_UNF_AVPLAY_ATTR_ID_LOW_DELAY, &stLowdelayAttr);
                if (Ret != HI_SUCCESS)
                {
                    sample_printf("call HI_UNF_AVPLAY_SetAttr HI_UNF_AVPLAY_ATTR_ID_LOW_DELAY failed.\n");
                    goto WIN_DETATCH;
                }
            }

            Ret = HI_UNF_AVPLAY_Start(pCodec->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
            if (Ret != HI_SUCCESS)
            {
                sample_printf("call HI_UNF_AVPLAY_Start failed.\n");
                goto WIN_DETATCH;
            }
        }
    }

    g_StopThread = HI_FALSE;
    for (index = 0; index < CurCodecNum; index++)
    {
        pCodec = &g_stCodec[index];
        pthread_create(&pCodec->EsThread, HI_NULL, (HI_VOID *)EsTthread, (HI_VOID *)pCodec);
    }

    while (1)
    {
        if (g_AutoCrcEnable == HI_TRUE)
        {
            usleep(30*1000);
            if (g_EsThreadExit == HI_TRUE)
            {
                break;
            }

            continue;
        }

        printf("please input the q to quit!, s to toggle spdif pass-through, h to toggle hdmi pass-through\n");
        SAMPLE_GET_INPUTCMD(InputCmd);

        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }

        //FOR MVC TEST
        if ('3' == InputCmd[0] && 'd' == InputCmd[1]  )
        {
            HI_UNF_DISP_Set3DMode(HI_UNF_DISPLAY1,
            HI_UNF_DISP_3D_FRAME_PACKING,
            HI_UNF_ENC_FMT_1080P_24_FRAME_PACKING);
        }

#ifdef HI_TEE_SUPPORT
        if ('t' == InputCmd[0] || 'T' == InputCmd[0])
        {
            if(stAvTVPAttr.bEnable == HI_TRUE)
            {
                sample_printf("call HI_UNF_AVPLAY_SetAttr TVP false.\n");
                stAvTVPAttr.bEnable = HI_FALSE;
            }
            else
            {
                sample_printf("call HI_UNF_AVPLAY_SetAttr TVP true.\n");
                stAvTVPAttr.bEnable = HI_TRUE;
            }

            stStopAttr.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
            stStopAttr.u32TimeoutMs = 0;
            HI_UNF_AVPLAY_Stop(g_stCodec[0].hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &stStopAttr);

            Ret = HI_UNF_AVPLAY_SetAttr(g_stCodec[0].hAvplay, HI_UNF_AVPLAY_ATTR_ID_TVP, &stAvTVPAttr);
            if (Ret != HI_SUCCESS)
            {
                sample_printf("call HI_UNF_AVPLAY_SetAttr TVP failed.\n");
                break;
            }

            Ret = HI_UNF_AVPLAY_Start(g_stCodec[0].hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
            if (Ret != HI_SUCCESS)
            {
                sample_printf("call HI_UNF_AVPLAY_Start failed.\n");
                break;
            }
        }
#endif
    }

    g_StopThread = HI_TRUE;
    for (index = 0; index < CurCodecNum; index++)
    {
        pCodec = &g_stCodec[index];
        pthread_join(pCodec->EsThread, HI_NULL);
        stStopAttr.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
        stStopAttr.u32TimeoutMs = 0;
        HI_UNF_AVPLAY_Stop(pCodec->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &stStopAttr);
    }

WIN_DETATCH:
    for (index = 0; index < CurCodecNum; index++)
    {
        pCodec = &g_stCodec[index];
        HI_UNF_VO_SetWindowEnable(pCodec->hWin, HI_FALSE);
        HI_UNF_VO_DetachWindow(pCodec->hWin, pCodec->hAvplay);
    }

VCHN_CLOSE:
    for (index = 0; index < CurCodecNum; index++)
    {
        pCodec = &g_stCodec[index];
        HI_UNF_AVPLAY_ChnClose(pCodec->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
    }

VO_DESTROY:
    for (index = 0; index < CurCodecNum; index++)
    {
        pCodec = &g_stCodec[index];
        HI_UNF_VO_DestroyWindow(pCodec->hWin);
    }

AVPLAY_DESTROY:
    for (index = 0; index < CurCodecNum; index++)
    {
        pCodec = &g_stCodec[index];
        HI_UNF_AVPLAY_Destroy(pCodec->hAvplay);
    }

VO_DEINIT:
    HIADP_VO_DeInit();

DISP_DEINIT:
    HIADP_Disp_DeInit();

AVPLAY_DEINIT:
    HI_UNF_AVPLAY_DeInit();

SYS_DEINIT:
    HI_SYS_DeInit();
    for (index = 0; index < CurCodecNum; index++)
    {
        pCodec = &g_stCodec[index];
        fclose(pCodec->pVidEsFile);
        pCodec->pVidEsFile = HI_NULL;

        if (pCodec->bCRCEnable == HI_TRUE)
        {
            ExitCrcEnvironment(pCodec);
        }
    }

#ifdef HI_TEE_SUPPORT
    if (bHaveTVPInst == HI_TRUE)
    {
        DeInitSecEnvironment();
    }
#endif

    sample_printf("Finish, sample exit!\n");

    return HI_SUCCESS;
}


