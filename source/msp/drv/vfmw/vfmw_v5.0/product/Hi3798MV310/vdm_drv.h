

/***********************************************************************
*
* Copyright (c) 2009 Hisilicon - All Rights Reserved
*
* File: $vdm_drv.h$
* Date: $2009/05/08$
* Revision: $v1.0$
* Purpose: VDEC driver interface.
*
* Change History:
*
* Date       Author            Change
* ======     ======            ======
* 20090508               Original
*
************************************************************************/

#ifndef __VDM_DRV_HEADER__
#define __VDM_DRV_HEADER__
#include "vfmw.h"
#include "sysconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VDH_IDLE                  (0)
#define VDH_BUSY                  (1)

#ifdef  CFG_VDH_TIME_OUT
#define MAX_TIME_VDM_DEC          (CFG_VDH_TIME_OUT)
#else
#define MAX_TIME_VDM_DEC          (500)        // ms
#endif

#define COUNT_WAIT_NO_ISR         (400)        // x10ms
#define MAX_TIME_WAIT_MORE_START  (200)        // ms

#define VDMDRV_OK                 (0)
#define VDMDRV_ERR                (-1)

#define MSG_SLOT_SIZE             (256)  //һ��SLOT��С, WORD
#define UP_MSG_SLOT_NUM           (2)
#define MAX_UP_MSG_SLICE_NUM      (200)  //HEVC�����200��slice
#define UP_MSG_SIZE               (MAX_UP_MSG_SLICE_NUM*4)  //һ��slice��Ϣ��ռ4word
#define LUMA_HISTORGAM_NUM        (32)

typedef enum
{
    VDH_STATE_REG        = 1,
    INT_STATE_REG        = 2,
    INT_MASK_REG         = 3,
    VCTRL_STATE_REG      = 4,
    MMU_INT_STATE_REG    = 5,
    MMU_ERR_RDADDR_REG   = 6,
    MMU_ERR_WRADDR_REG   = 7,
} REG_ID_E;

typedef enum
{
    VDM_NULL_STATE       = 0,
    VDM_DECODE_STATE     = 1,
    VDM_REPAIR_STATE_0   = 2,  // First repair
    VDM_REPAIR_STATE_1   = 3   // Second repair, only used for AVS field mode repair
} VDMDRV_STATEMACHINE_E;

typedef enum
{
    VDMDRV_SLEEP_STAGE_NONE = 0,      // δ����
    VDMDRV_SLEEP_STAGE_PREPARE,       // �յ������������δ�������
    VDMDRV_SLEEP_STAGE_SLEEP          // ������
} VDMDRV_SLEEP_STAGE_E;

/////////////////////////////////////////////////////////////////////
/* add    defined attach attrs                         */
/////////////////////////////////////////////////////////////////////
typedef enum
{
    VDMDRV_PERFORMANCE_1080P30  = 0,    //�ۺϳ�һ·���������
    VDMDRV_PERFORMANCE_1080P60  = 1,
    VDMDRV_PERFORMANCE_1080P120 = 2,
    VDMDRV_PERFORMANCE_4K30     = 3,
    VDMDRV_PERFORMANCE_4K60     = 4,
} VDMDRV_PERFORMANCE_E;

typedef enum
{
    VDMDRV_ATTACH_NULL = 0,         // û�а�
    VDMDRV_ATTACH_ALREADY = 1       // �����ð�ͨ��
} VDMDRV_ATTACH_MODE_E;

typedef enum
{
    VDMDRV_ATTACH_FOR_NONE = 0,        //  δ��
    VDMDRV_ATTACH_FOR_PERFORMANCE = 1,  //  �������ƶ���
    VDMDRV_ATTACH_FOR_RESOLUTION = 2   //  �ֱ������ƶ���
} VDMDRV_ATTACH_REASON_E;

#ifdef VFMW_MODULE_LOWDLY_SUPPORT
typedef enum
{
VDMDRV_CHAN_INT_STATE_BOTH_DEC_OVER = 1,
VDMDRV_CHAN_INT_STATE_PART_DEC_OVER,
VDMDRV_CHAN_INT_STATE_DEC_OVER,
} VDMDRV_CHAN_INT_STATE;
#endif

typedef enum
{
   ERR_RATIO_CORRECT_NOT_REPAIR = 0,
   ERR_RATIO_CORRECT_FORCE_REPAIR,
   ERR_RATIO_CORRECT_ABNORMAL,
   ERR_RATIO_CORRECT_NORMAL,
} VDMDRV_ERR_RATIO_CORRECT_TYPE;


typedef struct
{
    VDMDRV_ATTACH_MODE_E VdmAttachMode;
    VDMDRV_ATTACH_REASON_E VdmAttachReason[MAX_CHAN_NUM];
    SINT32 ChanIdAttachPlus1[MAX_CHAN_NUM];
    SINT32 AttachNum;
} VDMDRV_ATTACH_S;

typedef struct
{
    VDMDRV_PERFORMANCE_E VdmPreformance;
    VDMDRV_ATTACH_S VdmAttachStr;    //add ����vdh�Ƿ���ĳ��ͨ��ǿ��
} VDMDRV_EXT_S;

typedef enum
{
    VDH_FRAME_DEC = 0,
    VDH_SED_ONLY  = 1
} VDH_DEC_MODE_E;

//////////////////////////////////////////////////////////////////////
/* add end                                                          */
//////////////////////////////////////////////////////////////////////
typedef struct
{
    VDMDRV_STATEMACHINE_E VdmStateMachine;
    //SINT32 PriorTab[MAX_CHAN_NUM];
    SINT32 ErrRatio;
    SINT32 ChanId;
    VID_STD_E VidStd;

    UINT32 Clk;
    UINT32 StartTime;  // ms
    UINT32 CurrTime;   // ms
    SINT32 VdmTimeOut;
    UINT32 LastWaitMoreStartTime;
    SINT32 ChanResetFlag;
    SINT32 DspReloadFlag;
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    //add  fordsp
    VDMDRV_CHAN_INT_STATE ChanIntState;/*������ʾvdh�ж�״̬�ı�־��1:ͬʱ��⵽�к��жϺͽ�������ж�*/
#endif
    VOID *pDecParam;
    VDH_DEC_MODE_E VdhWorkMode;
} VDMDRV_PARAM_S;

typedef struct
{
    SINT32 PriorByChanId[MAX_CHAN_NUM];/*��ͨ����˳���ͨ�������ȼ���Ϣ*/
    SINT32 ChanIdTabByPrior[MAX_CHAN_NUM]; /* -1: ��λֵ��û��Ҫ�����ͨ��*/
    SINT32 ChanDecByVdhPlusOne[MAX_CHAN_NUM]; /* 0: δ��VDH���룬n: ���ڱ�(VDH_id + 1)����  5: ���ڱ�VEDU���� */
} CHAN_CTX;

/* VDM�����ڴ��ַ */
typedef struct
{
    // vdm register base vir addr
    SINT32    *pVdmRegVirAddr;
    SINT32    *pVdmResetVirAddr;

    SINT32    *pBpdRegVirAddr;
    SINT32    *pBpdResetVirAddr;

    // vdm hal base addr
    UADDR     HALMemBaseAddr;
    SINT32    HALMemSize;
    SINT32    VahbStride;
    UADDR     HALMemBaseAddr_Sec;
    SINT32    HALMemSize_Sec;

    //HEVC 10 Bit
    SINT32    VahbStride_2bit;
    /* message pool */
    UADDR     MsgSlotAddr[256];
    SINT32    ValidMsgSlotNum;

    /* vlc code table */
    UADDR     H264TabAddr;    /* 32 Kbyte */
    UADDR     MPEG2TabAddr;   /* 32 Kbyte */
    UADDR     MPEG4TabAddr;   /* 32 Kbyte */
    UADDR     AVSTabAddr;     /* 32 Kbyte */
    UADDR     VC1TabAddr;
    /* cabac table */
    UADDR     H264MnAddr;
    /* nei info for vdh for hevc  */ 
    UADDR     sed_top_phy_addr;
    UADDR     pmv_top_phy_addr;
    UADDR     pmv_left_phy_addr;
    UADDR     rcn_top_phy_addr;
    UADDR     mn_phy_addr;
    UADDR     tile_segment_info_phy_addr;
    UADDR     dblk_left_phy_addr;
    UADDR     dblk_top_phy_addr;
    UADDR     sao_left_phy_addr;
    UADDR     sao_top_phy_addr;
    UADDR     upmsgslot_phy_addr;
    UADDR     ppfd_phy_addr;
    SINT32    ppfd_buf_len;

    /*nei info for vdh */
    UADDR     SedTopAddr;     /* len = 64*4*x*/
    UADDR     PmvTopAddr;     /* len = 64*4*x*/
    UADDR     RcnTopAddr;     /* len = 64*4*x*/
    UADDR     ItransTopAddr;
    UADDR     DblkTopAddr;
    UADDR     PpfdBufAddr;
    UADDR     PpfdBufLen;

    UADDR     Dnr2dBufAddr;
    UADDR     IntensityConvTabAddr;
    UADDR     BitplaneInfoAddr;
    UADDR     Vp6TabAddr;
    UADDR     Vp8TabAddr;

    /* VP9 */
    UADDR    DblkLeftAddr;
    UADDR    Vp9ProbTabAddr;
    UADDR    Vp9ProbCntAddr;

    /* dnr mbinfo */
    UADDR     DnrMbInfoAddr;

    UINT8      *luma_2d_vir_addr;
    UADDR     luma_2d_phy_addr;
    UINT8      *chrom_2d_vir_addr;
    UADDR     chrom_2d_phy_addr;
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    /*ģ������ʱʹ�õ��к�*/
    UADDR     line_num_stAddr;
#endif

} VDMHAL_HWMEM_S;
typedef struct
{
    UINT32    LumaSumHigh;
    UINT32    LumaSumLow;
    UINT32    LumaHistorgam[LUMA_HISTORGAM_NUM];
} LUMA_INFO_S;

typedef struct
{
    SINT32 ModuleLowlyEnable;
    LUMA_INFO_S LumaInfo;
    VOID  *pTask;
    UINT8 FromISR;
} VDMDRV_PARAM_EXT_S;

/* ���뱨�����ݽṹ */
typedef struct
{
    UINT32    BasicCfg1;
    UINT32    VdmState;
    UINT32    Mb0QpInCurrPic;
    UINT32    SwitchRounding;
    UINT32    SedSta;
    UINT32    SedEnd0;

    UINT32    DecCyclePerPic;
    UINT32    RdBdwidthPerPic;
    UINT32    WrBdWidthPerPic;
    UINT32    RdReqPerPic;
    UINT32    WrReqPerPic;
    UINT32    LumaSumHigh;
    UINT32    LumaSumLow;
    UINT32    LumaHistorgam[LUMA_HISTORGAM_NUM];
} VDMHAL_BACKUP_S;

/* �޲��������ݽṹ */
typedef struct
{
    UINT8     CompressEn;
    UINT8     linear_en;
    UINT8     LossCompressEn;
    UINT8     LossLow2BitsEn;

    VID_STD_E VidStd;
    UADDR     ImageAddr;
    SINT32    YStride;
    SINT32    UVStride;
    UADDR     RefImageAddr;
    UADDR     CurrPmvAddr;
    SINT32    ImageWidth;
    SINT32    ImageHeight;
    SINT32    IsFrame;            // 0:fld, 1:frm
    SINT32    ImageCSP;           // 0:420, 1:400
    SINT32    ValidGroupNum;
    SINT32    rpr_ref_pic_type;
    SINT32    Pic_type;
    SINT32    FullRepair;
    UINT32    level;
    UINT32    CtbSize;            // ctbsize for hevc
    UINT32    tiles_enabled_flag; // for hevc

    struct
    {
        SINT16    StartMbn;
        SINT16    EndMbn;
    } MbGroup[MAX_UP_MSG_SLICE_NUM];

} VDMHAL_REPAIR_PARAM_S;

/* ���뱨�����ݽṹ */
typedef struct
{
    UINT32    RetType;
    UINT32    ImgStride;
    UINT32    UVStride;
    UINT32    DecSliceNum;
    UINT16    SliceMbRange[MAX_UP_MSG_SLICE_NUM + 1][2];
} VDMHAL_DEC_REPORT_S;

typedef struct
{
    UADDR  MemBaseAddr;
    SINT32 Size;
    SINT32 VdhId;
    UADDR  MemBaseAddr_Sec;
    SINT32 Size_Sec;
} VDMHAL_OPENPARAM_S;

typedef struct
{
    UINT32 *pMb0QpInCurrPic;
    SINT32 VdhId;
} BACKUP_INFO_S;

typedef struct
{
    VID_STD_E VidStd;
    VDMHAL_HWMEM_S *pHwMem;
    VOID *pDecParam;
    SINT32 VdhId;
} CFG_REPAIR_REG_S;

typedef struct
{
    VDMHAL_REPAIR_PARAM_S *pRepairParam;
    VDMHAL_HWMEM_S *pHwMem;
    SINT32 VdhId;
} CFG_REPAIR_MSG_S;


typedef struct
{
    VID_STD_E VidStd;
    VDMHAL_DEC_REPORT_S *pDecReport;
    SINT32 VdhId;
} MAKE_DEC_REPORT_S;

/*#########################################################################################
       ȫ�ֱ�������
 ##########################################################################################*/
extern VDMHAL_HWMEM_S    g_HwMem[MAX_VDH_NUM];
extern UINT32 g_UpMsg[MAX_VDH_NUM][UP_MSG_SIZE];   //������Ϣ����
extern VDMHAL_REPAIR_PARAM_S g_RepairParam[MAX_VDH_NUM][2];
extern VDMHAL_DEC_REPORT_S g_DecReport[MAX_VDH_NUM];
extern VDMHAL_BACKUP_S       g_BackUp[MAX_VDH_NUM];

extern UINT32 USE_FF_APT_EN;
extern VDMDRV_PARAM_S g_VdmDrvParam[MAX_VDH_NUM];
extern CHAN_CTX g_ChanCtx;
extern VDMDRV_EXT_S g_VdmExtParam[MAX_VDH_NUM];

VOID VDMDRV_Init( SINT32 VdhId );
VOID VDMDRV_Reset( SINT32 VdhId );
VOID VDMDRV_SetPriority(SINT32 *pPrioArray);
VOID VDMDRV_IsrProcess( SINT32 VdhId );
VOID VDMDRV_MMUIntServeProc(SINT32 vdh_id);
VOID VDMDRV_WakeUpVdm( VOID );
VOID VDMDRV_SetStateIdle( SINT32 VdhId );
SINT32 VDMDRV_IsVdmIdle( SINT32 VdhId );
SINT32 VDMDRV_WaitVdmReadyIfNoIsr( SINT32 VdhId );
SINT32 VDMDRV_GetCurrChanID(SINT32 VdhId);
SINT32 VDMDRV_IsVdmInISR(SINT32 VdhId);
SINT32 VDMDRV_PrepareSleep(SINT32 VdhId);
VDMDRV_SLEEP_STAGE_E VDMDRV_GetSleepStage(SINT32 VdhId);
VOID VDMDRV_ForceSleep(SINT32 VdhId);
VOID VDMDRV_ExitSleep(SINT32 VdhId);
VOID VDMDRV_ClearChanIsDec( SINT32 ChanID );
SINT32 VDMDRV_AvsFirstFldNeedRepair(VID_STD_E VidStd, VOID *pDecParam, SINT32 VdhId);
SINT32 VDMDRV_AvsSecondFldNeedRepair(VID_STD_E VidStd, VOID *pDecParam, SINT32 VdhId);
SINT32 VDMDRV_IsMpeg4NvopCopy(VID_STD_E VidStd, VOID *pDecParam);
SINT32 VDMDRV_IsVc1SkpicCopy(VID_STD_E VidStd, VOID *pDecParam);
SINT32 VDMDRV_IsVp6NvopCopy(VID_STD_E VidStd, VOID *pDecParam);
SINT32 VDMDRV_IsVp9RptFrmCopy(VID_STD_E VidStd, VOID *pDecParam);
SINT32 VDMDRV_IsCopy(VID_STD_E VidStd, VOID *pDecParam);
VOID VDMDRV_SetChanIsDec( SINT32 ChanID, SINT32 VdhID );
VOID VDMDRV_ClearChanIsDec( SINT32 ChanID );
SINT32 VDMDRV_IsChanDec( SINT32 ChanID );
VOID VDMDRV_ResetVDH(SINT32 ChanID);
VOID VDMDRV_ParamInit(VOID);
VOID VDMDRV_MarkReloadDsp(SINT32 VdhId, SINT32 ChanID);
VOID VDMDRV_UpdateMatchMode(SINT32 VdhId, SINT32 ChanID);

SINT32 VDMDRV_GetMb0QpInCurrPic(SINT32 VdhId);
SINT32 VDMDRV_GetSwitchRounding(SINT32 VdhId);

#ifdef __cplusplus
}
#endif


#endif  //__VDM_DRV_H__
