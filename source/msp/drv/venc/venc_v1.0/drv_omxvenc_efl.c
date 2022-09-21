#include "drv_venc_efl.h"
#include "drv_omxvenc_efl.h"
#include "drv_venc_osal.h"
#include "hi_drv_mmz.h"
#include "hi_drv_mem.h"

#include "hal_venc.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

extern OPTM_VENC_CHN_S g_stVencChn[HI_VENC_MAX_CHN];
extern VeduEfl_ChnCtx_S VeduChnCtx[HI_VENC_MAX_CHN];
extern VeduEfl_IpCtx_S VeduIpCtx;

VENC_BUFFER_S g_stKernelOmxmmz[HI_VENC_MAX_CHN][OMX_OUTPUT_PORT_BUFFER_MAX];

HI_U32 g_map_count = 0;
HI_U32 g_ummap_count = 0;

#define D_VENC_GET_CHN(u32VeChn, hVencChn) \
    do {\
        if (hVencChn == NULL)\
        {\
            u32VeChn = HI_VENC_MAX_CHN;\
            break;\
        }\
        u32VeChn = 0; \
        while (u32VeChn < HI_VENC_MAX_CHN)\
        {   \
            if (g_stVencChn[u32VeChn].hVEncHandle == hVencChn)\
            { \
                break; \
            } \
            u32VeChn++; \
        } \
    } while (0)

#define D_VENC_GET_CHN_BY_UHND(u32VeChn, hVencUsrChn) \
    do {\
        if (hVencUsrChn == HI_INVALID_HANDLE)\
        {\
            u32VeChn = HI_VENC_MAX_CHN;\
            break;\
        }\
        u32VeChn = 0; \
        while (u32VeChn < HI_VENC_MAX_CHN)\
        {   \
            if (g_stVencChn[u32VeChn].hUsrHandle == hVencUsrChn)\
            { \
                break; \
            } \
            u32VeChn++; \
        } \
    } while (0)
/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflPutMsg_OMX(queue_info_s* queue, HI_U32 MsgID, HI_U32 Status, void* MsgData)
{
    int ret = 0;
    queue_data_s QueueData;

    if (!queue)
    {
        HI_ERR_VENC("null point!!\n");
        return HI_FAILURE;
    }

    if (queue->bToOMX && MsgData)
    {
        memcpy(&QueueData.unFrmInfo.msg_info_omx.buf, MsgData, sizeof(venc_user_buf));
    }

    QueueData.bToOMX = queue->bToOMX;
    ret = VENC_DRV_MngQueue(queue, &QueueData, MsgID, Status);

    if ((ret == HI_SUCCESS))
    {
        VENC_DRV_EflWakeUpThread();
    }

    return ret;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflGetMsg_OMX(queue_info_s* queue, venc_msginfo* pmsg_info)
{
    queue_data_s Queue_Data;

    if (VENC_DRV_MngDequeue(queue, &Queue_Data))
    {
        return HI_FAILURE;
    }

    if (!Queue_Data.bToOMX)
    {
        HI_WARN_VENC("%s,%d not match to OMX!\n", __func__, __LINE__);
        return HI_FAILURE;
    }

    memcpy(pmsg_info, &Queue_Data.unFrmInfo.msg_info_omx, sizeof(venc_msginfo));

    return 0;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
#if 1
HI_S32 VENC_DRV_EflMMapToKernel_OMX(HI_U32 ChanId, HI_MMZ_BUF_S* pMMZbuf)
{
    HI_S32 s32Ret = 0,i = 0;
    VENC_BUFFER_S sMBufVenc   = {0};

    if(!pMMZbuf)
    {
       HI_ERR_VENC("%s(),%d, bad input!!\n",__func__,__LINE__);
       return HI_FAILURE;
    }

    sMBufVenc.u32StartPhyAddr = pMMZbuf->phyaddr;
    sMBufVenc.u32Size         = pMMZbuf->bufsize;

    s32Ret = HI_DRV_VENC_Map(&sMBufVenc);
    if (HI_SUCCESS == s32Ret)
    {
       pMMZbuf->kernel_viraddr = (HI_VOID *)sMBufVenc.pu8StartVirAddr;
       for(i = 0; i< OMX_OUTPUT_PORT_BUFFER_MAX;i++)
       {
            if (0 == g_stKernelOmxmmz[ChanId][i].pu8StartVirAddr)
            {
                g_stKernelOmxmmz[ChanId][i].pu8StartVirAddr = sMBufVenc.pu8StartVirAddr;
                g_stKernelOmxmmz[ChanId][i].u32StartPhyAddr = pMMZbuf->phyaddr;
                break;
            }
       }

    }
    else
    {   pMMZbuf->kernel_viraddr = (HI_VOID *)NULL;}

    return s32Ret;
}

HI_S32 VENC_DRV_EflUMMapToKernel_OMX(HI_U32 ChanId, HI_MMZ_BUF_S* pMMZbuf)
{
    HI_S32 i = 0;
    VENC_BUFFER_S sMBufVenc   = {0};
    if(!pMMZbuf)
    {
       HI_ERR_VENC("%s(),%d, bad input!!\n",__func__,__LINE__);
       return HI_FAILURE;
    }
    sMBufVenc.u32StartPhyAddr = (HI_U32)pMMZbuf->phyaddr;

    for (i = 0;i < OMX_OUTPUT_PORT_BUFFER_MAX; i++)
    {
        if (g_stKernelOmxmmz[ChanId][i].u32StartPhyAddr == sMBufVenc.u32StartPhyAddr)
        {
            sMBufVenc.pu8StartVirAddr = g_stKernelOmxmmz[ChanId][i].pu8StartVirAddr;
            g_stKernelOmxmmz[ChanId][i].u32StartPhyAddr = 0;
            g_stKernelOmxmmz[ChanId][i].pu8StartVirAddr = 0;
            break;
       }
    }
    HI_DRV_VENC_Unmap(&sMBufVenc);
    return HI_SUCCESS;
}
#endif


HI_S32 VENC_DRV_EflFlushOutputPort_OMX(VeduEfl_EncPara_S *pEncPara, VEDU_LOCK_FLAG *pflag, HI_BOOL bIntra)
{
    queue_data_s QueueData;
    HI_S32 s32Ret = 0;

    if (pEncPara->StreamQueue_OMX->bStrmLock)
    {
        VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, pflag);

        while (pEncPara->StreamQueue_OMX->bStrmLock)  //mutex with the stop processing add by sdk
        {
            msleep(2);
        }

        VENC_DRV_OsalLock( VeduIpCtx.pChnLock, pflag);
    }

    while ((!VENC_DRV_MngQueueEmpty(pEncPara->StreamQueue_OMX)) && (!s32Ret))
    {
        s32Ret |= VENC_DRV_MngDequeue(pEncPara->StreamQueue_OMX, &QueueData);

        if (!s32Ret && QueueData.bToOMX)
        {
            pEncPara->stStat.StreamQueueNum--;
            QueueData.unFrmInfo.msg_info_omx.buf.data_len = 0;
            VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_OUTPUT_DONE, s32Ret , &(QueueData.unFrmInfo.msg_info_omx.buf));
            pEncPara->stStat.MsgQueueNum++;
        }

        HI_INFO_VENC("############ flush output port!\n");
    }

    HI_INFO_VENC("############## flush output port ok!put message!\n");

    if (!bIntra)
    {
        VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_FLUSH_OUTPUT_DONE, s32Ret , NULL);
        pEncPara->stStat.MsgQueueNum++;
    }

    return s32Ret;
}

HI_S32 VENC_DRV_EflFlushInputPort_OMX(VeduEfl_EncPara_S* pEncPara, HI_U32 u32ChnID, HI_BOOL bIntra)
{
    HI_S32 s32Ret = 0;

    queue_data_s QueueData;

    while ((!VENC_DRV_MngQueueEmpty(pEncPara->FrameQueue_OMX)) && (!s32Ret))
    {
        s32Ret |= VENC_DRV_MngDequeue(pEncPara->FrameQueue_OMX, &QueueData);

        if (!s32Ret && QueueData.bToOMX)
        {
            pEncPara->stStat.QueueNum--;
            QueueData.unFrmInfo.msg_info_omx.buf.data_len = 0;
            VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_INPUT_DONE, s32Ret , &(QueueData.unFrmInfo.msg_info_omx.buf));
            pEncPara->stStat.MsgQueueNum++;
        }

        HI_INFO_VENC("############ flush input port!\n");
    }

    HI_INFO_VENC("############## flush input port ok!\n");

    if (!bIntra)
    {
        VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_FLUSH_INPUT_DONE, HI_SUCCESS , NULL);
        pEncPara->stStat.MsgQueueNum++;
    }

    return s32Ret;
}

HI_S32 VENC_DRV_EflFlushPort_OMX(VeduEfl_EncPara_S* EncHandle, HI_U32 u32PortIndex, HI_BOOL bIntra)
{
    VeduEfl_EncPara_S  *pEncPara;
    //venc_msginfo msg_info;

    VEDU_LOCK_FLAG flag;
    HI_U32 u32ChnID;
    HI_S32 s32Ret1 = 0;
    HI_S32 s32Ret2 = 0;

    D_VENC_GET_CHN(u32ChnID,EncHandle);
    D_VENC_CHECK_CHN(u32ChnID);

    pEncPara  = EncHandle;
    if(u32PortIndex != ALL_PORT && u32PortIndex > OUTPUT_PORT)
    {
        HI_ERR_VENC("[%s]: bad PortIndex(%d)!!\n",__func__,u32PortIndex);
        return HI_FAILURE;
    }

    VENC_DRV_OsalLock( VeduIpCtx.pChnLock, &flag);
    if( (OUTPUT_PORT == u32PortIndex) || (ALL_PORT == u32PortIndex) )
    {
        s32Ret1 = VENC_DRV_EflFlushOutputPort_OMX(pEncPara, &flag, bIntra);
    }

    VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );

    if((INPUT_PORT == u32PortIndex) || (ALL_PORT == u32PortIndex))
    {
        s32Ret2 = VENC_DRV_EflFlushInputPort_OMX(pEncPara, u32ChnID, bIntra);
    }

    return (s32Ret1||s32Ret2);
}
/*************************************************************************************/
#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
