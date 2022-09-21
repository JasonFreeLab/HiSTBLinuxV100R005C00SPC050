/******************************************************************************

  Copyright (C), 2013-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_vdec_usrdata.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/01/31
  Description   :
  History       :
  1.Date        : 2013/01/31
    Author      : sdk
    Modification: Created file

******************************************************************************/

/******************************* Include Files *******************************/

/* Sys headers */

/* Unf headers */
#include "hi_unf_common.h"

/* Drv headers */
#include "hi_kernel_adapt.h"

/* Local headers */
#include "vfmw.h"
#include "drv_vdec_private.h"
#include "drv_vdec_buf_mng.h"
#include "drv_vdec_usrdata.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/***************************** Macro Definition ******************************/

#define I_FRAME 1
#define P_FRAME 2
#define B_FRAME 3

#define MAX_USERDATA_IN_ONE_FRAME (4)
#define VDEC_USERDATA_ONLY_SUPPORT_CC (1)
/*************************** Structure Definition ****************************/

typedef struct
{
    HI_HANDLE hBuf;
    HI_BOOL bUsed;
    USRDAT astRefFrame[MAX_USERDATA_IN_ONE_FRAME];
    HI_U8 u8DataCnt;
}USRDATA_PARAM_S;

/***************************** Global Definition *****************************/

/************************* ** Extern function declaration ********************/
HI_S32 VDEC_FindChannelHandleByInstance(HI_HANDLE hHandle, VDEC_CHANNEL_S **pstChan);

/***************************** Static Definition *****************************/

static USRDATA_PARAM_S g_stUsrData[HI_VDEC_MAX_INSTANCE_NEW][HI_VDEC_SUPPORT_USERDATA_TYPE_NUM];

/*********************************** Code ************************************/

HI_S32 USRDATA_Init(HI_VOID)
{
    HI_S32 InstIndex;
    HI_S32 UserdataTypeIndex;

    for (InstIndex = 0; InstIndex < HI_VDEC_MAX_INSTANCE_NEW; InstIndex++)
    {
        for (UserdataTypeIndex = 0; UserdataTypeIndex < HI_VDEC_SUPPORT_USERDATA_TYPE_NUM; UserdataTypeIndex++)
        {
            g_stUsrData[InstIndex][UserdataTypeIndex].u8DataCnt = 0;
            memset(g_stUsrData[InstIndex][UserdataTypeIndex].astRefFrame, 0x0, sizeof(g_stUsrData[InstIndex][UserdataTypeIndex].astRefFrame));
            g_stUsrData[InstIndex][UserdataTypeIndex].hBuf = HI_INVALID_HANDLE;
            g_stUsrData[InstIndex][UserdataTypeIndex].bUsed = HI_FALSE;
        }
    }

    return HI_SUCCESS;
}

HI_S32 USRDATA_DeInit(HI_VOID)
{
    HI_S32 InstIndex;
    USERDATA_TYPE_E VdecUserdataType;

    for (InstIndex = 0; InstIndex < HI_VDEC_MAX_INSTANCE_NEW; InstIndex++)
    {
        for (VdecUserdataType = 0; VdecUserdataType < HI_VDEC_SUPPORT_USERDATA_TYPE_NUM; VdecUserdataType++)
        {
            if (g_stUsrData[InstIndex][VdecUserdataType].bUsed)
            {
                USRDATA_Free(InstIndex, VdecUserdataType);
            }
            else
            {
                g_stUsrData[InstIndex][VdecUserdataType].u8DataCnt = 0;
                g_stUsrData[InstIndex][VdecUserdataType].hBuf = HI_INVALID_HANDLE;
                g_stUsrData[InstIndex][VdecUserdataType].bUsed = HI_FALSE;
            }

            memset(g_stUsrData[InstIndex][VdecUserdataType].astRefFrame, 0, sizeof(g_stUsrData[InstIndex][VdecUserdataType].astRefFrame));
        }
    }

    return HI_SUCCESS;
}

HI_S32 USRDATA_Alloc(HI_HANDLE hHandle, HI_DRV_VDEC_USERDATABUF_S *pstBuf)
{
    HI_S32 s32Ret;
    HI_HANDLE hBuf;
    BUFMNG_INST_CONFIG_S stBufInstCfg;

    if ((hHandle >= HI_VDEC_MAX_INSTANCE_NEW) || (HI_NULL == pstBuf) || (g_stUsrData[hHandle][pstBuf->UserDataType].bUsed))
    {
        HI_ERR_VDEC("bad param!\n");

        return HI_FAILURE;
    }

    hBuf = hHandle + HI_VDEC_MAX_INSTANCE_NEW + pstBuf->UserDataType;

    /* Create buffer manager instance */
    stBufInstCfg.enAllocType = BUFMNG_ALLOC_INNER;
    stBufInstCfg.u32PhyAddr = 0;
    stBufInstCfg.pu8UsrVirAddr = HI_NULL;
    stBufInstCfg.pu8KnlVirAddr = HI_NULL;
    stBufInstCfg.u32Size = pstBuf->u32Size;
	#ifdef HI_TEE_SUPPORT
    stBufInstCfg.bTvp          = HI_FALSE;
	#endif
    snprintf(stBufInstCfg.aszName, sizeof(stBufInstCfg.aszName),"VDEC_UsrData%02d", (HI_U8)hHandle);
    s32Ret = BUFMNG_Create(hBuf, &stBufInstCfg);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VDEC("BUFMNG_Create err:%#x!\n", s32Ret);
        return HI_FAILURE;
    }

    /* Output phy addr */
    pstBuf->u32PhyAddr = stBufInstCfg.u32PhyAddr;
    HI_INFO_VDEC("USRDATA_Alloc: %#x %dB\n", pstBuf->u32PhyAddr, pstBuf->u32Size);

    g_stUsrData[hHandle][pstBuf->UserDataType].bUsed = HI_TRUE;
    g_stUsrData[hHandle][pstBuf->UserDataType].hBuf = hBuf;
    g_stUsrData[hHandle][pstBuf->UserDataType].u8DataCnt = 0;

    memset(g_stUsrData[hHandle][pstBuf->UserDataType].astRefFrame, 0x0, sizeof(g_stUsrData[hHandle][pstBuf->UserDataType].astRefFrame));

    return HI_SUCCESS;
}

HI_S32 USRDATA_SetUserAddr(HI_HANDLE hHandle, HI_U64 u64Addr, USERDATA_TYPE_E UserDataType)
{
    if (hHandle >= HI_VDEC_MAX_INSTANCE_NEW)
    {
        return HI_FAILURE;
    }

    HI_INFO_VDEC("USRDATA_SetUserAddr: %#llx\n", u64Addr);

    return BUFMNG_SetUserAddr(g_stUsrData[hHandle][UserDataType].hBuf, u64Addr);
}

HI_S32 USRDATA_Free(HI_HANDLE hHandle, USERDATA_TYPE_E UserDataType)
{
    if ((hHandle >= HI_VDEC_MAX_INSTANCE_NEW) || (UserDataType >= VDEC_USRDATA_TYPE_INDEX_BUTT))
    {
        return HI_FAILURE;
    }

    if (HI_INVALID_HANDLE != g_stUsrData[hHandle][UserDataType].hBuf)
    {
        BUFMNG_Destroy(g_stUsrData[hHandle][UserDataType].hBuf);
    }

    g_stUsrData[hHandle][UserDataType].bUsed = HI_FALSE;
    g_stUsrData[hHandle][UserDataType].hBuf = HI_INVALID_HANDLE;
    g_stUsrData[hHandle][UserDataType].u8DataCnt = 0;

    return HI_SUCCESS;
}

HI_S32 USRDATA_GlobalFree(HI_HANDLE hHandle)
{
    HI_S32 s32Ret = HI_SUCCESS;
    USERDATA_TYPE_E UserDataType;
    for (UserDataType = 0; UserDataType < HI_VDEC_SUPPORT_USERDATA_TYPE_NUM; UserDataType++)
    {
        s32Ret |= USRDATA_Free(hHandle, UserDataType);
    }

    return s32Ret;
}

HI_S32 USRDATA_Start(HI_HANDLE hHandle)
{
    return USRDATA_GlobalReset(hHandle);
}

HI_S32 USRDATA_Stop(HI_HANDLE hHandle)
{
    return USRDATA_GlobalReset(hHandle);
}

HI_S32 USRDATA_Reset(HI_HANDLE hHandle, USERDATA_TYPE_E UserDataType)
{
    if (hHandle >= HI_VDEC_MAX_INSTANCE_NEW)
    {
        return HI_FAILURE;
    }

    g_stUsrData[hHandle][UserDataType].u8DataCnt = 0;
    memset(g_stUsrData[hHandle][UserDataType].astRefFrame, 0x0, sizeof(g_stUsrData[hHandle][UserDataType].astRefFrame));
    BUFMNG_Reset(g_stUsrData[hHandle][UserDataType].hBuf);

    return HI_SUCCESS;
}

HI_S32 USRDATA_GlobalReset(HI_HANDLE hHandle)
{
    HI_S32 s32Ret = HI_SUCCESS;
    USERDATA_TYPE_E UserDataType;
    for (UserDataType = 0; UserDataType < HI_VDEC_SUPPORT_USERDATA_TYPE_NUM; UserDataType++)
    {
        s32Ret |= USRDATA_Reset(hHandle, UserDataType);
    }

    return s32Ret;
}

static HI_S32 USRDATA_GetVdecUserDataTypeByUnfUserDataType(HI_UNF_VIDEO_USERDATA_TYPE_E UnfUserDataType, USERDATA_TYPE_E *pVdecUserDataType)
{
    switch (UnfUserDataType)
    {
        case HI_UNF_VIDEO_USERDATA_DVB1_CC:
            *pVdecUserDataType = VDEC_USRDATA_TYPE_CC;
            break;

        case HI_UNF_VIDEO_USERDATA_AFD:
            *pVdecUserDataType = VDEC_USRDATA_TYPE_AFD;
            break;

        default:
            HI_ERR_VDEC("Not support user data type = %d!\n", UnfUserDataType);

            return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 USRDATA_GetUnfUserDataTypeByVdecUserDataType(USERDATA_TYPE_E VdecUserDataType, HI_UNF_VIDEO_USERDATA_TYPE_E *pUnfUserDataType)
{
    switch (VdecUserDataType)
    {
        case VDEC_USRDATA_TYPE_CC:
            *pUnfUserDataType = HI_UNF_VIDEO_USERDATA_DVB1_CC;
            break;

        case VDEC_USRDATA_TYPE_AFD:
            *pUnfUserDataType =  HI_UNF_VIDEO_USERDATA_AFD;
            break;

        default:
            HI_ERR_VDEC("Not support user data type = %d!\n", VdecUserDataType);

            return HI_FAILURE;
    }

    return HI_SUCCESS;
}


HI_S32 USRDATA_Acq(HI_HANDLE hHandle, VDEC_VIDEO_USERDATA_S *pstUsrData, HI_UNF_VIDEO_USERDATA_TYPE_E *penType)
{
    HI_S32 s32Ret;
    BUFMNG_BUF_S stBuf;
    USERDATA_TYPE_E VdecUserDataType;

    if ((hHandle >= HI_VDEC_MAX_INSTANCE_NEW) || (HI_NULL == pstUsrData) || (HI_NULL == penType))
    {
        return HI_FAILURE;
    }

    s32Ret = USRDATA_GetVdecUserDataTypeByUnfUserDataType(*penType, &VdecUserDataType);
    if (s32Ret != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    s32Ret = BUFMNG_AcqReadBuffer(g_stUsrData[hHandle][VdecUserDataType].hBuf, &stBuf);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }
    else
    {
        *penType = stBuf.u32Marker;
        memcpy(pstUsrData, stBuf.pu8KnlVirAddr, sizeof(VDEC_VIDEO_USERDATA_S));
        return HI_SUCCESS;
    }
}

HI_S32 USRDATA_Rls(HI_HANDLE hHandle, VDEC_VIDEO_USERDATA_S* pstUsrData, HI_UNF_VIDEO_USERDATA_TYPE_E *penType)
{
    HI_S32 s32Ret;
    BUFMNG_BUF_S stBuf;
    USERDATA_TYPE_E VdecUserDataType;

    if (hHandle >= HI_VDEC_MAX_INSTANCE_NEW)
    {
        return HI_FAILURE;
    }

    s32Ret = USRDATA_GetVdecUserDataTypeByUnfUserDataType(*penType, &VdecUserDataType);
    if (s32Ret != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    stBuf.pu8KnlVirAddr = HI_NULL;
    stBuf.pu8UsrVirAddr = (HI_U8*)(HI_SIZE_T)(pstUsrData->pu8Buffer - sizeof(VDEC_VIDEO_USERDATA_S));
    stBuf.u32Size = sizeof(VDEC_VIDEO_USERDATA_S) + pstUsrData->u32Length;

    s32Ret = BUFMNG_RlsReadBuffer(g_stUsrData[hHandle][VdecUserDataType].hBuf, &stBuf);

    return s32Ret;
}

HI_S32 USRDATA_Put(HI_HANDLE hHandle, USRDAT* pstUsrData, HI_UNF_VIDEO_USERDATA_TYPE_E enType)
{
    HI_S32 s32Ret;
    HI_BOOL bOverFlow = HI_FALSE;
    BUFMNG_BUF_S stBuf;
    VDEC_VIDEO_USERDATA_S *pstPutData;
    VDEC_CHANNEL_S *pstChan = HI_NULL;
    USERDATA_TYPE_E VdecUserDataType;

    s32Ret = USRDATA_GetVdecUserDataTypeByUnfUserDataType(enType, &VdecUserDataType);
    if (s32Ret != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    stBuf.u32Size = sizeof(VDEC_VIDEO_USERDATA_S) + pstUsrData->data_size;
    s32Ret = BUFMNG_GetWriteBuffer(g_stUsrData[hHandle][VdecUserDataType].hBuf, &stBuf);

    if (HI_ERR_BM_BUFFER_FULL == s32Ret)
    {
        BUFMNG_Reset(g_stUsrData[hHandle][VdecUserDataType].hBuf);
        bOverFlow = HI_TRUE;
        s32Ret = BUFMNG_GetWriteBuffer(g_stUsrData[hHandle][VdecUserDataType].hBuf, &stBuf);
    }

    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    pstPutData = (VDEC_VIDEO_USERDATA_S *)stBuf.pu8KnlVirAddr;
    pstPutData->enBroadcastProfile = HI_UNF_VIDEO_BROADCAST_DVB;
    pstPutData->enPositionInStream = pstUsrData->from;
    pstPutData->u32Pts = (HI_U32)pstUsrData->PTS;
    pstPutData->u32SeqCnt = pstUsrData->seq_cnt;
    pstPutData->u32SeqFrameCnt = pstUsrData->seq_img_cnt;
    pstPutData->u32Length = pstUsrData->data_size;
    pstPutData->bBufferOverflow = bOverFlow;
    pstPutData->bTopFieldFirst = pstUsrData->top_field_first;

    s32Ret = VDEC_FindChannelHandleByInstance(hHandle, &pstChan);

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_VDEC("call VDEC_FindChannelHandleByInstance failed! ret:%d\n", s32Ret);
        return HI_FAILURE;
    }

#ifdef HI_TEE_SUPPORT
    if (HI_TRUE == pstChan->bTvp)
    {
    }
    else
#endif
    {
        memcpy(stBuf.pu8KnlVirAddr + sizeof(VDEC_VIDEO_USERDATA_S), pstUsrData->data, pstUsrData->data_size);
    }

    pstPutData->pu8Buffer = (HI_U64)(HI_SIZE_T)(stBuf.pu8UsrVirAddr + sizeof(VDEC_VIDEO_USERDATA_S));
    stBuf.u32Marker = enType;

    s32Ret =  BUFMNG_PutWriteBuffer(g_stUsrData[hHandle][VdecUserDataType].hBuf, &stBuf);

    return s32Ret;
}

HI_S32 USRDATA_SetEosFlag(HI_HANDLE hHandle)
{
    HI_S32 i;
    HI_U8 u8DataCnt;
    USERDATA_TYPE_E VdecUserDataType;
    HI_UNF_VIDEO_USERDATA_TYPE_E UnfUserDataType;

    if (hHandle >= HI_VDEC_MAX_INSTANCE_NEW)
    {
        return HI_FAILURE;
    }

    for (VdecUserDataType = 0; VdecUserDataType < HI_VDEC_SUPPORT_USERDATA_TYPE_NUM; VdecUserDataType++)
    {
        if (USRDATA_GetUnfUserDataTypeByVdecUserDataType(VdecUserDataType, &UnfUserDataType) != HI_SUCCESS)
        {
            continue;
        }

        u8DataCnt = g_stUsrData[hHandle][VdecUserDataType].u8DataCnt;

        /* Put reference frame */
        for (i = 0; i < u8DataCnt; i++)
        {
            USRDATA_Put(hHandle, &(g_stUsrData[hHandle][VdecUserDataType].astRefFrame[i]), UnfUserDataType);
        }

        g_stUsrData[hHandle][VdecUserDataType].u8DataCnt = 0;
    }

    return HI_SUCCESS;
}

static HI_S32 USRDATA_CC(HI_HANDLE hHandle, USRDAT *pstUsrData)
{
    HI_S32 i;
    HI_U8 u8DataCnt;
#if (1==VDEC_USERDATA_NEED_ARRANGE)

    /* I_FRAME or P_FRAME, sort */
    if ((I_FRAME == pstUsrData->pic_coding_type) || (P_FRAME == pstUsrData->pic_coding_type))
    {
        u8DataCnt = g_stUsrData[hHandle][VDEC_USRDATA_TYPE_CC].u8DataCnt;

        /* Belongs to the same frame with last data */
        if (pstUsrData->pic_num_count == g_stUsrData[hHandle][VDEC_USRDATA_TYPE_CC].astRefFrame[0].pic_num_count)
        {
            if (u8DataCnt >= MAX_USERDATA_IN_ONE_FRAME)
            {
                HI_WARN_VDEC("Too many data in a frame.\n");
            }
            else
            {
                /* Only save new data */
                g_stUsrData[hHandle][VDEC_USRDATA_TYPE_CC].astRefFrame[u8DataCnt] = *pstUsrData;
                g_stUsrData[hHandle][VDEC_USRDATA_TYPE_CC].u8DataCnt++;
            }
        }
        /* New frame data */
        else
        {
            /* Put reference frame */
            for (i = 0; i < u8DataCnt; i++)
            {
                USRDATA_Put(hHandle, &(g_stUsrData[hHandle][VDEC_USRDATA_TYPE_CC].astRefFrame[i]), HI_UNF_VIDEO_USERDATA_DVB1_CC);
            }

            /* Save new data */
            g_stUsrData[hHandle][VDEC_USRDATA_TYPE_CC].astRefFrame[0] = *pstUsrData;
            g_stUsrData[hHandle][VDEC_USRDATA_TYPE_CC].u8DataCnt = 1;
        }

    }
    /* B_FRAME or other error frame, put directly */
    else
#endif
    {
        return USRDATA_Put(hHandle, pstUsrData, HI_UNF_VIDEO_USERDATA_DVB1_CC);
    }

    return HI_SUCCESS;
}

HI_S32 USRDATA_Arrange(HI_HANDLE hHandle, USRDAT* pstUsrData)
{
#if (VDEC_USERDATA_ONLY_SUPPORT_CC == 0)
    HI_U32 u32ID;
    HI_U8 u8Type;
#endif

    if ((hHandle >= HI_VDEC_MAX_INSTANCE_NEW) || (HI_NULL == pstUsrData) ||
       (0 == pstUsrData->data_size))
    {
        return HI_FAILURE;
    }

#if (VDEC_USERDATA_ONLY_SUPPORT_CC == 0)
    if (pstUsrData->data_size > 5)
    {
        u32ID = *((HI_U32*)pstUsrData->data);
        u8Type = pstUsrData->data[4];
        if (VDEC_USERDATA_IDENTIFIER_DVB1 == u32ID)
        {
            if (VDEC_USERDATA_TYPE_DVB1_CC == u8Type)
            {
                return USRDATA_CC(hHandle, pstUsrData);
            }
            else if (VDEC_USERDATA_TYPE_DVB1_BAR == u8Type)
            {
                return USRDATA_Put(hHandle, pstUsrData, HI_UNF_VIDEO_USERDATA_DVB1_BAR);
            }
        }
        else if (VDEC_USERDATA_IDENTIFIER_AFD == u32ID)
        {
            return USRDATA_Put(hHandle, pstUsrData, HI_UNF_VIDEO_USERDATA_AFD);
        }
        else
        {
            return USRDATA_Put(hHandle, pstUsrData, HI_UNF_VIDEO_USERDATA_UNKNOWN);
        }
    }
    else
    {
        return USRDATA_Put(hHandle, pstUsrData, HI_UNF_VIDEO_USERDATA_UNKNOWN);
    }

    return HI_FAILURE;
#else
    return USRDATA_CC(hHandle, pstUsrData);
#endif
}

EXPORT_SYMBOL(USRDATA_Rls);
EXPORT_SYMBOL(USRDATA_Acq);
EXPORT_SYMBOL(USRDATA_Alloc);
EXPORT_SYMBOL(USRDATA_SetUserAddr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

