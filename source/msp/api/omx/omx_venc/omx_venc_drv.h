/*========================================================================
Open MAX   Component: Video Decoder
This module contains the class definition for openMAX decoder component.
========================================================================== */
#ifndef __VENC_DRV_CTX_H__
#define __VENC_DRV_CTX_H__

#include "hi_drv_venc.h"
#include "OMX_Types.h"

#define VENC_NAME    "/dev/hi_venc"   //"/dev/hisi_venc"
#define VENC_MAX_CHN  (8)
#define HI_INVALID_HANDLE (0xffffffff)

typedef struct OPTM_venc_channel_S
{
    OMX_U32 chan_handle;
    OMX_S32 state;                /* 0: not create yet ; 1: start; 2:stop */
    venc_chan_cfg chan_cfg;
} venc_channel_S;

typedef struct OPTM_venc_stream_S
{
    //OMX_S32        chan_handle;
    void*      pStrmBufVirAddr;
    OMX_U32   u32StrmBufPhyAddr;
    OMX_U32   u32BufSize;
} venc_stream_buf_S;

typedef struct
{
    HI_U32 ProfileIDC;
    HI_U32 FrameWidthInMb;
    HI_U32 FrameHeightInMb;
    HI_U8  FrameCropLeft;
    HI_U8  FrameCropRight;
    HI_U8  FrameCropTop;
    HI_U8  FrameCropBottom;
} OMXVenc_H264e_SPS_S;

typedef struct
{
    HI_U32  ConstIntra;
    HI_S32  ChrQpOffset;
    HI_U32  H264HpEn;
    HI_U32  H264CabacEn;
    //HI_S32 *pScale8x8;
    HI_S32  Scale8x8[128];
} OMXVenc_H264e_PPS_S;

typedef struct
{
    /* header parameter */
    HI_U8  SpsStream[16];
    HI_U8  PpsStream[320];
    HI_U32 SpsBits;
    HI_U32 PpsBits;

    /*sps & pps info*/
    OMXVenc_H264e_SPS_S stSPSData;
    OMXVenc_H264e_PPS_S stPPSData;
} omx_sps_pps_data_S;

typedef struct venc_driver_context
{
    OMX_S32 video_driver_fd;                                //设备文件标识符，当video_driver_fd>0时，设备已经被打开(通常在初始化的时候打开)

    venc_channel_S venc_chan_attr;
    venc_stream_buf_S venc_stream_addr;
    omx_sps_pps_data_S stStrmHeadData;
} venc_drv_context;

OMX_S32 venc_init_drv_context(venc_drv_context* drv_ctx);

void venc_deinit_drv_context(venc_drv_context*  drv_ctx);

OMX_S32 channel_create(venc_drv_context* drv_ctx);

OMX_S32 channel_destroy(venc_drv_context* drv_ctx);

OMX_S32 channel_start(venc_drv_context* drv_ctx);

OMX_S32 channel_stop(venc_drv_context* drv_ctx);

OMX_S32 channel_request_IFrame(venc_drv_context* drv_ctx);

//OMX_S32 channel_pause(venc_drv_context *drv_ctx);

//OMX_S32 channel_resume(venc_drv_context *drv_ctx);

OMX_S32 channel_flush_port(venc_drv_context* drv_ctx,
                           OMX_U32 flush_dir);

OMX_S32 channel_get_msg(venc_drv_context* drv_ctx,
                        venc_msginfo* msginfo);

OMX_S32 channel_queue_Image(venc_drv_context* drv_ctx,
                            venc_user_buf* puser_buf);

OMX_S32 channel_queue_stream(venc_drv_context* drv_ctx, venc_user_buf* puser_buf);

#if 0
OMX_S32 channel_bind_buffer(venc_drv_context* drv_ctx,
                            venc_user_buf* puser_buf);

OMX_S32 channel_unbind_buffer(venc_drv_context* drv_ctx,
                              venc_user_buf* puser_buf);
#endif

void venc_get_default_attr(venc_drv_context* drv_ctx);

OMX_S32 venc_mmap_kerel_vir(venc_drv_context* drv_ctx, venc_user_buf* puser_buf);
OMX_S32 venc_unmmap_kerel_vir(venc_drv_context* drv_ctx, venc_user_buf* puser_buf);
OMX_S32 channel_get_sps_pps(venc_drv_context *drv_ctx,  DRV_VIDEO_PPS_SPS_DATA *pParameterSet);
OMX_S32 channel_set_attr(venc_drv_context* drv_ctx);
OMX_S32 channel_get_attr(venc_drv_context* drv_ctx);

OMX_U32 channel_get_current_level(OMX_U32 EncWidth, OMX_U32 EncHeight);
#endif
