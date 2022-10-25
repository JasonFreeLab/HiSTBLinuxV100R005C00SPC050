#ifndef __VPSS_IN_3798MV310_H__
#define __VPSS_IN_3798MV310_H__

#include "vpss_common.h"
#include "drv_vdec_ext.h"

#include "vpss_in_common.h"
#include "vpss_common.h"
#include "vpss_src.h"
#include "vpss_sttinf.h"
#include "vpss_img.h"
#include "vpss_his.h"
#include "vpss_rwzb.h"
#include "vpss_trans_fb.h"

#include "vpss_cbb_hal.h"
#include "vpss_mcdei.h"

typedef enum
{
    VPSS_IN_INFO_SRC,
    VPSS_IN_INFO_WBC,
    VPSS_IN_INFO_REF,
    VPSS_IN_INFO_STREAM,
    VPSS_IN_INFO_WBCREG_VA,
    VPSS_IN_INFO_WBCREG_PA,
    VPSS_IN_INFO_NR,
    VPSS_IN_INFO_DIE,
    VPSS_IN_INFO_CORRECT_FIELD,
    VPSS_IN_INFO_BLEND_REF,
    VPSS_IN_INFO_BLEND_WBC,
    VPSS_IN_INFO_RGME,
    VPSS_IN_INFO_BLKMV,
    VPSS_IN_INFO_PRJH,
    VPSS_IN_INFO_PRJV,
    VPSS_IN_INFO_BUTT
} VPSS_IN_INFO_TYPE_E;


typedef enum
{
    VPSS_SET_INFO_INPUT_CFG,
    VPSS_SET_INFO_PTS,
    VPSS_SET_INFO_MCDEI,
    VPSS_SET_INFO_BUTT
} VPSS_SET_INFO_TYPE_E;

typedef struct
{
    VPSS_VERSION_E enVersion;
    VPSS_IN_MODE_E enMode;
    PFN_IN_RlsCallback pfnRlsCallback;
    PFN_IN_RlsCallback pfnAcqCallback;
    HI_HANDLE hSource;

    HI_DRV_VPSS_PRODETECT_E enProgInfo;
    HI_BOOL bProgRevise;
    HI_BOOL bAlwaysFlushSrc;
    HI_DRV_COLOR_SPACE_E enSrcCS;

    HI_BOOL bSecure;


    VPSS_IN_STREAM_INFO_S stStreamInfo;
    HI_DRV_VIDEO_ORIGINAL_INFO_S stOriInfo;
    HI_U32                u32ScenceChgCnt;

    VPSS_SET_DBG_INFO_S stDbginfo;

    /*spinlock for VPSS_SRC_S*/
    VPSS_OSAL_SPIN stSrcSpin;
    VPSS_TRANS_FB_INFO_S stTransFbInfo;

    VPSS_IMAGELIST_INFO_S *pstSrcImagesList;
    HI_DRV_VIDEO_FRAME_S stSrcImage;
    VPSS_HIS_INFO_S *pstHisInfo;

    VPSS_SRC_S          stSrc;
    VPSS_WBC_S          stWbcInfo[2];
    VPSS_STTWBC_S       stSttWbc[2];
    VPSS_DIESTINFO_S    stDieStInfo[2];
    VPSS_NRMADINFO_S    stNrMadInfo[2];
    VPSS_MCDEI_INFO_S   stMcdeiInfo[2];
    VPSS_IN_IMAGELIST_STATE_S stListState;
} VPSS_IN_ENTITY_S;

typedef HI_S32 (*PFN_IN_RefreshList)(VPSS_IN_ENTITY_S *pstEntity);

typedef HI_S32 (*PFN_IN_GetProcessImage)(VPSS_IN_ENTITY_S *pstEntity, HI_DRV_VIDEO_FRAME_S **ppstFrame);

typedef HI_S32 (*PFN_IN_CompleteImage)(VPSS_IN_ENTITY_S *pstEntity);

typedef HI_S32 (*PFN_IN_GetInfo)(VPSS_IN_ENTITY_S *pstEntity,
                                 VPSS_IN_INFO_TYPE_E enType,
                                 HI_DRV_BUF_ADDR_E enLR,
                                 HI_VOID *pstInfo);

typedef HI_S32 (*PFN_IN_SetInfo)(VPSS_IN_ENTITY_S *pstEntity,
                                 VPSS_SET_INFO_TYPE_E enType,
                                 HI_DRV_BUF_ADDR_E enLR,
                                 HI_VOID *pstInfo);

typedef HI_S32 (*PFN_IN_Reset)(VPSS_IN_ENTITY_S *pstEntity);

typedef HI_S32 (*PFN_IN_PutImage)(VPSS_IN_ENTITY_S *pstEntity, HI_DRV_VIDEO_FRAME_S *pstFrame);

typedef HI_S32 (*PFN_IN_GetImage)(VPSS_IN_ENTITY_S *pstEntity, HI_DRV_VIDEO_FRAME_S *pstFrame);

typedef struct
{
    PFN_IN_GetProcessImage pfnGetProcessImage;
    PFN_IN_CompleteImage   pfnCompleteImage;
    PFN_IN_Reset           pfnReset;
    PFN_IN_GetInfo         pfnGetInfo;
    PFN_IN_SetInfo         pfnSetInfo;
    PFN_IN_RefreshList     pfnRefresh;
} VPSS_IN_INTF_S;


HI_S32 VPSS_IN_Init(VPSS_IN_ENTITY_S *pstEntity, VPSS_IN_ENV_S stEnv);

HI_S32 VPSS_IN_GetIntf(VPSS_IN_ENTITY_S *pstEntity, VPSS_IN_INTF_S *pstIntf);

HI_S32 VPSS_IN_SetAttr(VPSS_IN_ENTITY_S *pstEntity, VPSS_IN_ATTR_S stAttr);

HI_S32 VPSS_IN_GetAttr(VPSS_IN_ENTITY_S *pstEntity, VPSS_IN_ATTR_S *pstAttr);

HI_S32 VPSS_IN_SetSrcMode(VPSS_IN_ENTITY_S *pstEntity, VPSS_IN_SOURCE_S stMode);

HI_S32 VPSS_IN_DeInit(VPSS_IN_ENTITY_S *pstEntity);


#endif
