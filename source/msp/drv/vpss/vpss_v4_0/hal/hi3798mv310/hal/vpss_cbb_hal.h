/******************************************************************************

 Copyright @ Hisilicon Technologies Co., Ltd. 1998-2015. All rights reserved.

 ******************************************************************************
  File Name     : vpss_hal_3798mv310.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2016/1/6
  Last Modified :
  Description   : vpss_hal_3798mv310.h header file
  Function List :
  History       :
  1.Date        : 2016/1/6
    Author      : sdk
    Modification: Created file

******************************************************************************/
#ifndef __VPSS_HAL_3798MV310_H__
#define __VPSS_HAL_3798MV310_H__

#include "hi_type.h"
#include "hi_drv_mmz.h"
#include "vpss_common.h"
#include "hi_drv_vpss.h"
#include "vpss_sttinf.h"
#include "vpss_wbc.h"
#include "vpss_rwzb.h"
#include "vpss_his.h"
#include "drv_pq_ext.h"
#include "vpss_wbc_mcdei.h"
#include "vpss_stt_mcdei.h"
#include "vpss_fb.h"

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/
#define DEF_LOGIC_TIMEOUT       0xffffffff//0xe4e1c0
#define VPSS_LOGIC_CLOCK_SEL    0
#define HAL_VERSION_3798M       0x300
#define HAL_VERSION_3798MV310   0x4000

#define VPSS0_BASE_ADDR         0xf8cb0000
#define VPSS1_BASE_ADDR         0xffffffff
#define VPSS_REG_SIZE           ((sizeof(VPSS_REG_S) + 15) & 0xFFFFFFF0)
#define DEF_VPSS_HAL_PORT_NUM   1
//#define DEF_HI_DRV_VPSS_PORT_MAX_NUMBER   2
#define DEF_VPSS_HAL_REF_LIST_NUM 4

#define VPSS_REG_SIZE_CALC(start, end)\
    (offsetof(VPSS_REG_S, end) + sizeof(HI_U32) -\
     offsetof(VPSS_REG_S, start))

#define VPSS_HAL_CHECK_IP_VAILD(enIP) \
    do{\
        if((enIP != VPSS_IP_0)&&(enIP != VPSS_IP_1))\
        {\
            VPSS_ERROR("VPSS IP%d, is Not Vaild\n", enIP);\
            return HI_FAILURE;\
        }\
    }while(0)

#define VPSS_HAL_CHECK_NODE_ID_VAILD(enTaskNodeId) \
    do{\
        if(enTaskNodeId >= VPSS_HAL_TASK_TYPE_BUTT)\
        {\
            VPSS_ERROR("VPSS NODE ID%d, is Not Vaild\n", enTaskNodeId);\
            return HI_FAILURE;\
        }\
    }while(0)

#define VPSS_HAL_CHECK_INIT(bInit) \
    do{\
        if (HI_FALSE == bInit){\
            VPSS_ERROR("VPSS HAL Is Not Init\n");\
            return HI_FAILURE;\
        }\
    }while(0)


#define VPSS_HAL_CHECK_NULL_PTR(ptr) \
    do{\
        if (HI_NULL == ptr){\
            VPSS_ERROR("pointer is NULL!\n");\
            return HI_FAILURE;\
        }\
    }while(0)

#define VPSS_ZME_ADDR_GET(appviraddr)   ((appviraddr) + 0x2000)
#define VPSS_MEM_CLEAR(memblk) do {\
        memset(&(memblk), 0x0, sizeof(memblk));\
    } while (0)

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

typedef enum hiVPSS_IP_E
{
    VPSS_IP_0 = 0,
    VPSS_IP_1,
    VPSS_IP_BUTT
} VPSS_IP_E;
typedef enum hiVPSS_HAL_TASK_NODE_E
{
    VPSS_HAL_TASK_NODE_2D_FIELD = 0,
    VPSS_HAL_TASK_NODE_2D_FRAME,
    VPSS_HAL_TASK_NODE_3D,
    VPSS_HAL_TASK_NODE_HDR,
    VPSS_HAL_TASK_LOWQUALITY,
    VPSS_HAL_TASK_NODE_H265_DEI,
    VPSS_HAL_TASK_NODE_2D_LAST2FIELD,
    VPSS_HAL_TASK_TYPE_BUTT
} VPSS_HAL_TASK_TYPE_E;


//4p/c ���ֲ�ͬ��NODE ����, cts. 4k����

typedef enum hiVPSS_HAL_NODE_TYPE_E //�����߼������
{
    VPSS_HAL_NODE_2D_FRAME          = 0, //2D����
    VPSS_HAL_NODE_2D_FRAME_VIRTUAL  = 1, //2D��������˿�,ת��ʹ��
    VPSS_HAL_NODE_2D_DEI            = 2, //2D����, hd
    VPSS_HAL_NODE_2D_DEI_VIRTUAL    = 3, //2D����, hd����˿�,ת��ʹ��
    VPSS_HAL_NODE_2D_FIELD          = 4, //2D����,��������
    VPSS_HAL_NODE_2D_FIELD_VIRTUAL  = 5, //2D����,������������˿�,ת��ʹ��
    VPSS_HAL_NODE_2D_SD_FIRST       = 6, //sd, ����, tnr, dei
    VPSS_HAL_NODE_2D_SD_SECOND      = 7, //sd, ����, snr, vhd0 funcs
    VPSS_HAL_NODE_2D_SD_VIRTUAL     = 8, //sd, ��������˿�,ת��ʹ��
    VPSS_HAL_NODE_2D_CTS10          = 9, //ֻ��2Dʱ��
    VPSS_HAL_NODE_2D_CTS10_VIRTUAL  = 10,//CTS10,����˿�

    VPSS_HAL_NODE_2D_UHD            = 11,
    VPSS_HAL_NODE_2D_UHD_VIRTUAL    = 12,

    VPSS_HAL_NODE_3D_FRAME_L        = 13,//3D����
    VPSS_HAL_NODE_3D_FRAME_R        = 14,//3D����

    VPSS_HAL_NODE_HDR_DETILE_NOALG  = 15,

    VPSS_HAL_NODE_2D_H265_STEP1_INTERLACE       = 16,
    VPSS_HAL_NODE_2D_H265_STEP2_DEI             = 17,

    VPSS_HAL_NODE_2D_DEI_LAST_2FIELD            = 18,
    VPSS_HAL_NODE_2D_DEI_LAST_2FIELD_VIRTUAL    = 19,

    VPSS_HAL_NODE_ROTATION_Y        = 20,//Y,C��ת
    VPSS_HAL_NODE_ROTATION_Y_VIRTUAL = 21,
    VPSS_HAL_NODE_ROTATION_C        = 22,//Y,C��ת
    VPSS_HAL_NODE_ROTATION_C_VIRTUAL = 23,


    VPSS_HAL_NODE_BUTT
} VPSS_HAL_NODE_TYPE_E;

typedef enum hiVPSS_HAL_OPCODE_E
{
    VPSS_OPCODE_SET         = 0x0,
    VPSS_OPCODE_GET,
    VPSS_OPCODE_CLEAR,
    VPSS_OPCODE_BUTT
} VPSS_HAL_OPCODE_E;

typedef enum hiVPSS_HAL_OPTYPE_E
{
    VPSS_OPTYPE_CLOCK       = 0x0,
    VPSS_OPTYPE_INT,
    VPSS_OPTYPE_ADDR_BASE_REG,
    VPSS_OPTYPE_ADDR_ALG_PARA,
    VPSS_OPTYPE_BUTT,
} VPSS_HAL_OPTYPE_E;

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/
typedef struct hiVPSS_HAL_CTX_S
{
    HI_BOOL         bInit;
    HI_BOOL         bClockEn;
    HI_U32          u32LogicVersion;

    HI_U32          u32BaseRegPhy;
    HI_U8          *pu8BaseRegVir;

    HI_U32          au32AppPhy[VPSS_HAL_NODE_BUTT];
    HI_U8          *apu8AppVir[VPSS_HAL_NODE_BUTT];
    MMZ_BUFFER_S    stRegBuf;

#ifdef HI_VPSS_SMMU_SUPPORT
    SMMU_BUFFER_S   stSDDeiBuf_MMU;
#else
    MMZ_BUFFER_S    stSDDeiBuf_MMZ;
#endif

    SMMU_BUFFER_S   stSDDeiBuf_TEE;

#ifdef VPSS_SUPPORT_OUT_TUNNEL
#ifdef HI_VPSS_SMMU_SUPPORT
    SMMU_BUFFER_S   stLowDelayBuf_MMU;
#else
    MMZ_BUFFER_S    stLowDelayBuf_MMZ;
#endif
#endif
} VPSS_HAL_CTX_S;

typedef struct hiVPSS_HAL_FRAME_S
{
    HI_DRV_FRAME_TYPE_E     eFrmType;
    HI_DRV_PIX_FORMAT_E     enFormat;
    HI_DRV_FIELD_MODE_E     enFieldMode;
    HI_DRV_PIXEL_BITWIDTH_E enBitWidth;

    HI_BOOL                 bProgressive;
    HI_BOOL                 bCompressd;
    HI_BOOL                 bUVInver;
    HI_BOOL                 bTopFirst;
    HI_BOOL                 bSecure;

    HI_U32                  u32Width;
    HI_U32                  u32Height;

    HI_DRV_VID_FRAME_ADDR_S stAddr;
    HI_DRV_VID_FRAME_ADDR_S stAddr_LB;
    HI_DRV_VID_FRAME_ADDR_S stAddr_META;
    HI_U32                  u32MetaSize;
    HI_U32                  u32TunnelAddr;
} VPSS_HAL_FRAME_S;


typedef struct hiVPSS_HAL_PORT_INFO_S
{
    HI_BOOL     bEnable;
    HI_RECT_S   stInCropRect;           /* PORT CROP��Ϣ */
    HI_RECT_S   stVideoRect;            /* ��ʵ��ʾ���� */
    HI_RECT_S   stOutCropRect;
    HI_DRV_VPSS_ROTATION_E  enRotation; /* ��ת��Ϣ */
    HI_BOOL     bNeedFlip;
    HI_BOOL     bNeedMirror;
    HI_BOOL     bNeedRota;
    HI_BOOL     bConfig;
#ifdef VPSS_SUPPORT_OUT_TUNNEL
    HI_BOOL     bOutLowDelay;           /* tunnel out */
#endif
    VPSS_COLOR_E eLetterBoxColor;
    VPSS_HAL_FRAME_S        stOutInfo; /* PORT�����Ϣ */

    VPSS_FB_NODE_S stFrmNodeRoBuf;
} VPSS_HAL_PORT_INFO_S;

typedef struct hiVPSS_DIE_INFO_S
{
    HI_BOOL bBottom_first;
    VPSS_DIESTCFG_S stDieStCfg;
} VPSS_DIE_INFO_S;

typedef struct hiVPSS_NR_INFO_S
{
    HI_BOOL         bNrEn;
    VPSS_NRMADCFG_S stNrMadCfg;
} VPSS_NR_INFO_S;


typedef struct hiVPSS_MCDEI_RFR_S
{
    HI_BOOL bMcdeiEn;   //MCDEI����
    HI_BOOL bMedsEn;    //ME�²�������

    VPSS_HAL_FRAME_S    stRgmeWbc;   //rgme��д֡
    VPSS_HAL_FRAME_S    stRgmeRef[VPSS_RGME_WBC_MAX_NODE];//rgme�ο�֡
    VPSS_HAL_FRAME_S    stBlendWbc;  //blend��д֡
    VPSS_HAL_FRAME_S    stBlendRef;  //blend�ο�֡
} VPSS_MCDEI_RFR_S;

typedef struct hiVPSS_MCDEI_ST_S
{
    VPSS_ST_RGME_CFG_S   stRgmeCfg;   //rgme�˶���Ϣ
    VPSS_ST_BLKMV_CFG_S  stBlkmvCfg;  //blkmv�˶���Ϣ
    VPSS_ST_PRJH_CFG_S   stPrjhCfg;   //prjh�˶���Ϣ
    VPSS_ST_PRJV_CFG_S   stPrjvCfg;   //prjv�˶���Ϣ
} VPSS_MCDEI_ST_S;

typedef struct hiVPSS_STT_ADDR_S
{
    HI_U32                  u32stt_w_phy_addr;
    HI_U8                  *pu8stt_w_vir_addr;
} VPSS_STT_ADDR_S;

typedef struct hiVPSS_HAL_RefList
{
#ifdef HI_VPSS_SMMU_SUPPORT
    SMMU_BUFFER_S stRefListBuf_mmu;
#ifdef HI_TEE_SUPPORT
    SMMU_BUFFER_S stRefListBuf_tee;
#endif
#else
    MMZ_BUFFER_S  stRefListBuf_mmz;
#endif

    HI_DRV_VID_FRAME_ADDR_S stRefListAddr[DEF_VPSS_HAL_REF_LIST_NUM];
    HI_BOOL                 abRefNodeValid[DEF_VPSS_HAL_REF_LIST_NUM];
    HI_BOOL                 bRefListValid;
    HI_U32                  u32RefListHead;

} VPSS_HAL_RefList_S;


typedef struct hiVPSS_HAL_INFO_S
{
    VPSS_REG_S             *pstPqCfg;
    VPSS_HAL_NODE_TYPE_E    enNodeType;
    VPSS_HAL_FRAME_S        stInInfo;          //����Դ��Ϣ
    VPSS_HAL_FRAME_S        stInRefInfo[4];    //�ο�֡��Ϣ
    VPSS_HAL_FRAME_S        stInWbcInfo;       //��д��Ϣ
    VPSS_HAL_FRAME_S        stSDDeiFrame;      //sd dei temp frame info
    VPSS_RWZB_INFO_S        stRwzbInfo;
    HI_U32                  u32DetileFieldIdx;    //��tile ��ǰ3�����

    VPSS_NR_INFO_S          stNrInfo;
    VPSS_DIE_INFO_S         stDieInfo;
    VPSS_MCDEI_RFR_S        stMcdeiRfrInfo;     //mcdei��д��Ϣ
    VPSS_MCDEI_ST_S         stMcdeiStInfo;      //mcdei�˶���Ϣ
    VPSS_STT_ADDR_S         stSttAddr;          //�˶���Ϣ��ַ

    VPSS_HAL_PORT_INFO_S    astPortInfo[DEF_HI_DRV_VPSS_PORT_MAX_NUMBER];
    VPSS_HAL_RefList_S      *pstH265RefList;
    HI_DRV_VPSS_SCENEMODE_E enSceneMode;
    HI_S32                  s32InstanceID;
} VPSS_HAL_INFO_S;




typedef HI_S32 (*PF_NODE_CFG_FUNC) (VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy);


/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/
extern VPSS_HAL_CTX_S  stHalCtx[VPSS_IP_BUTT];

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

extern  HI_S32 VPSS_HAL_BaseFunc(VPSS_IP_E enIP, VPSS_HAL_OPCODE_E u32OpCode, VPSS_HAL_OPTYPE_E u32OpType,
                                 HI_VOID *pPtr1, HI_VOID *pPtr2);
extern  HI_S32 VPSS_HAL_DeInit(VPSS_IP_E enIP);
extern  HI_S32 VPSS_HAL_Init(VPSS_IP_E enIP);
extern  HI_S32 VPSS_HAL_SetClockEn(VPSS_IP_E enIP, HI_BOOL bClockEn);
extern  HI_S32 VPSS_HAL_StartLogic(VPSS_IP_E enIP, HI_BOOL abNodeVaild[VPSS_HAL_NODE_BUTT]);
extern HI_S32 VPSS_HAL_SetTaskInfo(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, VPSS_HAL_TASK_TYPE_E enTaskId,
                                   HI_BOOL bNodeList[VPSS_HAL_NODE_BUTT]);
extern HI_S32 VPSS_HAL_Set_2DDei_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy);
extern HI_S32 VPSS_HAL_Set_2DField_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy);
extern HI_S32 VPSS_HAL_Set_2DFrame_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy);
extern HI_S32 VPSS_HAL_Set_2DSDFirst_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy);
extern HI_S32 VPSS_HAL_Set_2DSDSecond_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy);
extern HI_S32 VPSS_HAL_Set_3DFrameL_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy);
extern HI_S32 VPSS_HAL_Set_3DFrameR_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy);

extern HI_S32 VPSS_HAL_Set_2D_UHDFrame_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy);
extern HI_S32 VPSS_HAL_Set_CTS10_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy);
extern HI_S32 VPSS_HAL_Set_RotaC_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy);
extern HI_S32 VPSS_HAL_Set_RotaY_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy);
extern HI_S32 VPSS_HAL_Set_HDR_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32 u32AppPhy);
extern HI_S32 VPSS_HAL_GetDetPixel(HI_U8 *pDstData, HI_U8 *pSrcData);
extern HI_S32 VPSS_HAL_Get_RwzbPixel(HI_U8 *pu8PixelBaseAddr_vir,
                                     VPSS_RWZB_INFO_S *pstRwzbInfo, HI_U32 u32YCMode, HI_BOOL bField);

extern HI_S32 VPSS_HAL_TunnelOut_GetBufAddr(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 u32PortID);
extern HI_VOID VPSS_HAL_DumpReg(VPSS_IP_E enIP, VPSS_HAL_NODE_TYPE_E enNodeId, HI_BOOL bRegValue);
extern HI_S32 VPSS_HAL_H265RefListDeInit(VPSS_HAL_RefList_S *pstRefList);
extern HI_S32 VPSS_HAL_H265RefListInit(VPSS_HAL_RefList_S *pstRefList, HI_S32 s32Width, HI_S32 s32Height, HI_DRV_PIX_FORMAT_E
                                       enFormat, HI_BOOL bSecure);
extern HI_S32 VPSS_HAL_SetNode_H265_Step1_Interlace(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo,
        HI_U32 *pu32AppVir, HI_U32 u32AppPhy);
extern HI_S32 VPSS_HAL_SetNode_H265_Step2_Dei(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo,
        HI_U32 *pu32AppVir, HI_U32 u32AppPhy);
extern HI_S32 VPSS_HAL_Set_2DDei_Last2Field_Node(VPSS_IP_E enIP, VPSS_HAL_INFO_S *pstHalInfo, HI_U32 *pu32AppVir, HI_U32
        u32AppPhy);
extern HI_S32 VPSS_HAL_GetNodeAddr(VPSS_IP_E enIP, HI_U32 u32NodeId, HI_U8 **pstRegAddr, HI_CHAR **ppNodeName);
extern HI_VOID VPSS_Hal_PrintHalInfo(struct seq_file *p, S_VPSS_REGS_TYPE *pstNodeReg);
extern HI_S32 VPSS_HAL_GetSystemTickCounter(VPSS_IP_E enIP, HI_U32 *ptickcnt, HI_U32 *pSystemClock);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VPSS_HAL_3798MV310_H__ */
