/*****************************************************************************
  Copyright (C), 2004-2014, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
  File Name     : drv_omxvenc.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/08/21
  Last Modified :
  Description   :
  Function List :
  History       :
  1.Date        :
  Author        : sdk
  Modification  : Created file
 ******************************************************************************/
#include "drv_win_ext.h"
#include "drv_venc_ext.h"
#include "drv_disp_ext.h"
#include "hi_drv_module.h"
#include "hi_drv_file.h"
#include "drv_venc_efl.h"
#include "drv_omxvenc_efl.h"
#include "drv_venc_buf_mng.h"
#include "drv_omxvenc.h"
#include "hi_mpi_venc.h"
#include "hi_drv_video.h"
#include "hi_kernel_adapt.h"

#include "hi_drv_sys.h"

//#include "drv_ndpt_ext.h"
//#include "drv_vi_ext.h"
#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

#define VENC_MAX_FRAME_LEN 200000
extern OPTM_VENC_CHN_S g_stVencChn[HI_VENC_MAX_CHN];

#ifdef __VENC_DRV_DBG__

extern HI_U32 TmpTime_dbg[100][7];
extern HI_U32 Isr_ID;
extern HI_U32 PutMsg_EBD_ID;
extern HI_U32 PutMsg_FBD_ID;
extern HI_U32 GetMsg_EBD_ID;
extern HI_U32 GetMsg_FBD_ID;
extern HI_BOOL flage_dbg;

#endif

#ifndef HI_ADVCA_FUNCTION_RELEASE
#define Smooth_printk printk
#else
#define Smooth_printk(format, arg...)
#endif


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

#define D_VENC_GET_PRIORITY_ID(s32VeChn, sPriorityID) \
    do {\
        sPriorityID = 0; \
        while (sPriorityID < HI_VENC_MAX_CHN)\
        {   \
            if (PriorityTab[0][sPriorityID] == s32VeChn)\
            { \
                break; \
            } \
            sPriorityID++; \
        } \
    } while (0)

#define D_VENC_CHECK_CHN(u32VeChn) \
    do {if (u32VeChn >= HI_VENC_MAX_CHN){ \
            return HI_ERR_VENC_CHN_NOT_EXIST; \
        } \
    } while (0)

enum
{
    OMX_VENC_YUV_420    = 0,
    OMX_VENC_YUV_422    = 1,
    OMX_VENC_YUV_444    = 2,
    OMX_VENC_YUV_NONE   = 3
};

enum
{
    OMX_VENC_V_U        = 0,
    OMX_VENC_U_V        = 1
};

enum
{
    OMX_VENC_STORE_SEMIPLANNAR    = 0,
    OMX_VENC_STORE_PACKAGE       = 1,
    OMX_VENC_STORE_PLANNAR      = 2
};

enum
{
    OMX_VENC_PACKAGE_UY0VY1      = 141/*0b10001101*/,
    OMX_VENC_PACKAGE_Y0UY1V        = 216/*0b11011000*/,
    OMX_VENC_PACKAGE_Y0VY1U     = 120/*0b01111000*/
};

HI_S32 VENC_DRV_QueueFrame_OMX(VeduEfl_EncPara_S* hVencChn, venc_user_buf* pstFrameInfo )     //add
{
    HI_S32 s32Ret;
    HI_U32 u32VeChn = 0;
    VeduEfl_EncPara_S*  pstEncChnPara ;
    HI_DRV_VIDEO_FRAME_S stFrame;
    memset(&stFrame, 0, sizeof(HI_DRV_VIDEO_FRAME_S));
    D_VENC_GET_CHN(u32VeChn, hVencChn);

    if (HI_VENC_MAX_CHN == u32VeChn )
    {
        HI_ERR_VENC("%s:: the handle(%p) does not create either!\n", __func__, hVencChn);

        return HI_FAILURE;
    }

    pstEncChnPara = hVencChn;

    if (HI_TRUE == pstEncChnPara->bNeverEnc)
    {
        pstEncChnPara->stSrcInfo.handle         = g_stVencChn[u32VeChn].hUsrHandle;
        pstEncChnPara->stSrcInfo.pfGetImage_OMX = VENC_DRV_EflGetImage_OMX;
        pstEncChnPara->stSrcInfo.pfPutImage     = HI_NULL;
        pstEncChnPara->bNeverEnc = HI_FALSE;
    }

    s32Ret = VENC_DRV_EflPutMsg_OMX(pstEncChnPara->FrameQueue_OMX, VENC_MSG_RESP_INPUT_DONE, 0, pstFrameInfo);

    if (!s32Ret)
    {
        pstEncChnPara->stStat.QueueNum++;
    }

    return s32Ret;
}

/////////////////////////////////////////////

HI_S32 VENC_DRV_QueueStream_OMX(VeduEfl_EncPara_S* hVencChn, venc_user_buf* pstFrameInfo )     //add
{
   HI_S32 s32Ret;
   HI_S32 s32VeChn = 0;
   VeduEfl_EncPara_S  *pstEncChnPara ;

   D_VENC_GET_CHN(s32VeChn, hVencChn);
   if(HI_VENC_MAX_CHN == s32VeChn )
   {
        HI_ERR_VENC("%s:: the handle(%p) does not start or even not be create either!\n", __func__, hVencChn);
       return HI_FAILURE;
   }
    pstEncChnPara = hVencChn;
   s32Ret = VENC_DRV_EflPutMsg_OMX(pstEncChnPara->StreamQueue_OMX,VENC_MSG_RESP_OUTPUT_DONE, 0, pstFrameInfo);
   if (!s32Ret)
   {
      pstEncChnPara->stStat.StreamQueueNum++;
   }
   return s32Ret;
}

HI_U32 QueueMsg_ID = 0;
extern HI_BOOL flage_dbg;

HI_S32 VENC_DRV_GetMessage_OMX(VeduEfl_EncPara_S* hVencChn, venc_msginfo* pmsg_info )
{
   HI_S32 s32Ret;
   HI_S32 s32VeChn = 0;
   venc_msginfo msg_info;
   VeduEfl_EncPara_S* pstEncChnPara;

   D_VENC_GET_CHN(s32VeChn, hVencChn);
   if(HI_VENC_MAX_CHN == s32VeChn )
   {
        HI_ERR_VENC("%s:: the handle(%p) does not start or even not be create either!\n", __func__, hVencChn);
       return HI_FAILURE;
   }
   if(!pmsg_info)
   {
       HI_ERR_VENC("%s invalid param,LINE:%d\n", __func__,__LINE__);
       return HI_FAILURE;
   }
    pstEncChnPara = hVencChn;

   s32Ret = VENC_DRV_EflGetMsg_OMX(pstEncChnPara->MsgQueue_OMX, &msg_info);
   if (HI_SUCCESS != s32Ret)
   {
        return HI_FAILURE;
   }


#ifdef __VENC_DRV_DBG__

   if (msg_info.msgcode == VENC_MSG_RESP_INPUT_DONE)   //FBD
   {
       if (GetMsg_EBD_ID < 100)
       {
           HI_DRV_SYS_GetTimeStampMs(&TmpTime_dbg[GetMsg_EBD_ID][5]);
           GetMsg_EBD_ID++;
       }
   }

   if(msg_info.msgcode == VENC_MSG_RESP_OUTPUT_DONE)
   {
       if (GetMsg_FBD_ID < 100)
       {
           HI_DRV_SYS_GetTimeStampMs(&TmpTime_dbg[GetMsg_FBD_ID][6]);
           GetMsg_FBD_ID++;
       }
       else if(flage_dbg)
       {
#if 0
            int i = 0;
            unsigned int diff[7] = {0};
            unsigned int total = 0;
            Smooth_printk("\n/******************************* BEGIN ****************************************/\n");
            Smooth_printk(" FrameID        queue_stream   isr   put_msg     get_msg  diff1 diff2 diff3   total_diff\n");
            for(i = 0;i<100;i++)
            {
               diff[0]=TmpTime_dbg[i][1] - TmpTime_dbg[i][0];
               diff[1]=TmpTime_dbg[i][2] - TmpTime_dbg[i][1];
               diff[2]=TmpTime_dbg[i][3] - TmpTime_dbg[i][1];
               diff[3]=TmpTime_dbg[i][4] - TmpTime_dbg[i][2];
               diff[4]=TmpTime_dbg[i][5] - TmpTime_dbg[i][3];
               diff[5]=TmpTime_dbg[i][6] - TmpTime_dbg[i][4];
               total  =TmpTime_dbg[i][6] - TmpTime_dbg[i][0];
               Smooth_printk(" %03d    %8d   %8d  |  %8d   %8d  | %8d  %8d  ||%8d||  \n",
                      i,diff[0],diff[1],diff[2],diff[3],diff[4],diff[5],total);
            }

            Smooth_printk("\n/*******************************  END *******************************************/\n");
#endif
            flage_dbg = 0;
       }
   }
#endif

   pstEncChnPara->stStat.MsgQueueNum--;
   memcpy(pmsg_info , &msg_info , sizeof(venc_msginfo));
   return HI_SUCCESS;
}

HI_S32 VENC_DRV_FlushPort_OMX(VeduEfl_EncPara_S* hVencChn, HI_U32 u32PortIndex)
{
   HI_S32 s32Ret;
   HI_S32 s32VeChn = 0;

   D_VENC_GET_CHN(s32VeChn, hVencChn);
   if(HI_VENC_MAX_CHN == s32VeChn )
   {
        HI_ERR_VENC("%s:: the handle(%p) does not start or even not be create either!\n", __func__, hVencChn);
       return HI_FAILURE;
   }

   s32Ret = VENC_DRV_EflFlushPort_OMX(hVencChn,u32PortIndex,HI_FALSE);
   return s32Ret;
}



HI_S32 VENC_DRV_MMZ_Map_OMX(HI_U32 ChanId, HI_MMZ_BUF_S* pMMZbuf)
{
   HI_S32 s32Ret;

   if(!pMMZbuf)
   {
      HI_ERR_VENC("%s:: bad input!!\n",__func__);
      return HI_FAILURE;
   }
   D_VENC_CHECK_CHN(ChanId);

   s32Ret = VENC_DRV_EflMMapToKernel_OMX(ChanId,pMMZbuf);
   if((s32Ret != HI_SUCCESS) || (NULL == pMMZbuf->kernel_viraddr))
   {
      HI_ERR_VENC("%s:: VENC_DRV_EflMMapToKernel failed!\n",__func__);
      return HI_FAILURE;
   }
   HI_INFO_VENC("map the Phyaddr = 0x%x==>VirAddr = %p\n",pMMZbuf->phyaddr,pMMZbuf->kernel_viraddr);
   return HI_SUCCESS;
}

HI_S32 VENC_DRV_MMZ_UMMap_OMX(HI_U32 ChanId, HI_MMZ_BUF_S* pMMZbuf)
{
   HI_S32 s32Ret;

   if(!pMMZbuf)
   {
      HI_ERR_VENC("%s:: bad input!!\n",__func__);
      return HI_FAILURE;
   }

   D_VENC_CHECK_CHN(ChanId);

   s32Ret = VENC_DRV_EflUMMapToKernel_OMX(ChanId,pMMZbuf);
   if( HI_SUCCESS != s32Ret )
   {
      HI_ERR_VENC("%s:: VENC_DRV_EflUMMapToKernel failed!\n",__func__);
      return HI_FAILURE;
   }
   return HI_SUCCESS;
}
#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

