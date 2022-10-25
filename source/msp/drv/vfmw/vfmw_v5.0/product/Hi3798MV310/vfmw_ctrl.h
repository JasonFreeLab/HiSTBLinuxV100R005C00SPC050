
#ifndef __VFMV_CTRL_H__
#define __VFMV_CTRL_H__
#include "vfmw.h"
#include "fsp.h"
#include "sysconfig.h"
#ifdef VFMW_H263_SUPPORT
#include "sdec_imedia.h"
#endif
#include "syntax.h"
#ifdef ENV_SOS_KERNEL
#include "vfmw_tee_client.h"
#endif
/*======================================================================*/
/*  ����                                                                */
/*======================================================================*/
#define VCTRL_OK                0
#define VCTRL_ERR              -1
#define VCTRL_ERR_VDM_BUSY     -2
#define VCTRL_ERR_NO_FSTORE    -3
#define VCTRL_ERR_NO_STREAM    -4

#define VCTRL_TRUE              1
#define VCTRL_FALSE             0

#define MAX_FRAME_SIZE             2048*2048

#define VCTRL_FIND_PTS          0
#define VCTRL_PTS_ILLEAGLE     -1
#define VCTRL_SEEKING_PTS      -2

#define VCTRL_ADD_EXTRA        1
#define VCTRL_IGNOR_EXTRA     2

#define MAX_USRDEC_FRAME_NUM        (16)

// time record pos
#define THREAD_START (0)
#define THREAD_END   (1)

#define SEGCOPY_START    (2)
#define SEGCOPY_END      (3)

#define MAP_START  (4)
#define MAP_END    (5)

#define SYNTAX_START   (6)
#define SYNTAX_END     (7)

#define VDH_START   (8)
#define VDH_END     (9)

#define ISR_START   (9)
#define ISR_END     (10)

#define NEXT_THREAD_START   (11)

//data record id
#define COPY_SIZE_DATA    (0)
#define VDH_DATA          (1)

#define MAX_RECORD_NUM    (15)

#define MAX_RECORD_POS    (12)   //TIME
#define MAX_RECORD_DATA    (2)   //DATA

/*======================================================================*/
/*  �ṹ��ö��                                                          */
/*======================================================================*/
/* ֡�漯�ϣ����ڵ���: ��ѯ�ж���֡�棬�����ݷֱ�Ϊ�� */
typedef struct hiVFMWFrameARRAY
{
    SINT32       s32FrameNum;
    SINT32       s32PixWidth;
    SINT32       s32PixHeight;
    SINT32       s32Stride;
    SINT32       s32ChromOfst;
    UADDR        s32PhyAddr[64];
} VFMW_FRAME_ARRAY_S;

/* ͨ����ص�ͳ����Ϣ */
typedef struct hiVFMW_CHAN_STAT
{
    UINT32        u32FrBeginTime;   /* ����֡�ʵĿ�ʼʱ�� */
    UINT32        u32FrImgNum;      /* ֡�� */
    UINT32        u32FrFrameRate;   /* ֡�� */

    /* ��֡ͳ�� */
    UINT32        u32SkipFind;        /* �⵽��skip֡��Ŀ */
    UINT32        u32SkipDiscard;     /* ���������skip֡��Ŀ */
    UINT32        u32IsFieldFlag;     /* ��ǰ��������е�֡�ǳ�ͼ��־������PVR������˻�ȡ����֡������ */

    VFMW_FRAME_ARRAY_S stFrameArray;
} VFMW_CHAN_STAT_S;

typedef struct hiVFMW_GLOBAL_STAT
{
    /* VDMռ����ͳ�� */
    UINT32        u32VdhStatisticStartTimeInMs; /* ͳ��VDMռ���ʵ���ʼʱ�� */
    UINT32        u32VdhLastStartTimeInMs;      /* ��һ������Ӳ����ʱ�� */
    UINT32        u32VdhWorkTimeInMs;           /* VDM�ۼƹ���ʱ�� */
    UINT32        u32VdhCycleTime;   /* ͨ��Cycleͳ�Ƶ�VDM�ۼƹ���ʱ�� */
    UINT32        u32VdhLoad;                   /* VDMռ���� */
    UINT32        u32VdhCycleLoad;  /* ͨ��Cycleͳ�Ƶ�VDMռ���� */
    UINT32        u32VdhIrqPerSec;     /* VDM ÿ���ж��� */

    /* VDM��������ͳ�� */
    UINT32        u32PicNum;
    UINT32        u32AccountVdhKiloCycle;
    UINT32        u32VdhKiloCyclePerSecond;
    UINT32        u32Period;
    /* SCDռ����ͳ�� */
    UINT32        u32ScdBeginTime;              /* ͳ��SCDռ���ʵ���ʼʱ�� */
    UINT32        u32ScdLastStartTime;          /* ��һ������Ӳ����ʱ�� */
    UINT32        u32ScdWorkTime;               /* SCD�ۼƹ���ʱ�� */
    UINT32        u32ScdLoad;                   /* SCDռ���� */

    UINT32        u32IsVdhEn;
} VFMW_GLOBAL_STAT_S;

#if 0
typedef struct
{
    SYNTAX_EXTRA_DATA_S *pstExtraData;
    IMAGE_VO_QUEUE     ImageQue;
    SINT32               ChanID;
} USER_CTX_S;
#endif

/* ArrangeMem�������ô��ݵ�ָʾ������ */
typedef enum
{
    CAP_HEVC_SPECIFIC     = -2,
    INVALID_CHAN_ID       = -1,
    VALID_CHAN_ID_START   = 0,
} ARRANGE_FLAG_E;

typedef enum
{
    VDM_SUPPORT_VP6       = 1,  /* 1<<0 */
    VDM_SUPPORT_BPD       = 2,  /* 1<<1 */
    VDM_SUPPORT_VCMP      = 4,  /* 1<<2 */
    VDM_SUPPORT_GMC       = 8,   /* 1<<3 */
    VDM_SUPPORT_DNR       = 16   /* 1<<4 */
} VDM_CHARACTER_E;

/* �̵߳�״̬ */
typedef enum hiTASKSTATE_E
{
    TASK_STATE_EXIT = 0,        /* �˳�, �߳�δ������������ */
    TASK_STATE_STOP,            /* ֹͣ���߳��Ѵ��������ڿ�ת������ֹͣ */
    TASK_STATE_RUNNING,         /* ���� */
    TASK_STATE_BUTT
} TASK_STATE_E;

/* ���̷߳�����ָ�� */
typedef enum hiTASKCMD_E
{
    TASK_CMD_NONE = 0,        /* ��ָ�� */
    TASK_CMD_START,           /* ����ָ���������ֹͣ״̬���߳� */
    TASK_CMD_STOP,            /* ָֹͣ�ֹͣ��������״̬���߳� */
    TASK_CMD_KILL,            /* ����ָ�ʹ�������л�ֹͣ״̬���߳���Ȼ�˳� */
    TASK_CMD_BUTT
} TASK_CMD_E;

/* ͨ���Ľ������ */
typedef enum hiChanDecCore
{
    DEC_CORE_VDM,
    DEC_CORE_IMEDIA_H263,
    DEC_CORE_IMEDIA_SORENSON,
    DEC_CORE_IMEDIA_VP6,
    DEC_CORE_IMEDIA_VP6F,
    DEC_CORE_IMEDIA_VP6A,
    DEC_CORE_BUTT
} CHAN_DEC_CORE_E;

/* ���һ֡״̬���� */
typedef enum hiLastFrameState
{
    LAST_FRAME_INIT = 0,
    LAST_FRAME_RECEIVE,
    LAST_FRAME_REPORT_SUCCESS,
    LAST_FRAME_REPORT_FAILURE,
    LAST_FRAME_REPORT_FRAMEID,
    LAST_FRAME_BUTT
} LAST_FRAME_STATE_E;

/*ͨ������״̬*/
typedef enum
{
    CHAN_NORMAL,  //ͨ������Run
    CHAN_FRAME_STORE_ALLOC, //ͨ�����ڷ���֡��
    CHAN_DESTORY,    //ͨ����������
} VFMW_CHANNEL_CONTROL_STATE_E;

typedef struct hiDRV_MEM_S
{
    MEM_RECORD_S  stVdmHalMem[MAX_VDH_NUM];      /* VDM HAL�ڴ� */
    MEM_RECORD_S  stScdCmnMem[MAX_SCD_NUM];      /* SCD �����ڴ� */
    #ifdef VFMW_VP9_SUPPORT
    #ifndef ENV_SOS_KERNEL
    MEM_RECORD_S  stVp9ProbMem[MAX_VDH_NUM];        /* VP9 ���ʱ��ڴ� */
    #endif
    #endif
    MEM_DESC_S    stExtHalMem;            /* ֧���ⲿ��hal���ڴ�*/
    MEM_RECORD_S  stVdmReg[MAX_VDH_NUM];
    MEM_RECORD_S  stFodReg;
    MEM_RECORD_S  stScdReg[MAX_SCD_NUM];
    MEM_RECORD_S  stBpdReg;
    MEM_RECORD_S  stSystemReg;      /* ϵͳ�Ĵ��������縴λFOD,VDM,SCD�� */
} DRV_MEM_S;

typedef struct hiDRV_IRQ_RECORD_S
{
    SINT32 VdhIrq[MAX_VDH_NUM];
    SINT32 ScdIrq[MAX_SCD_NUM];
    SINT32 vdh_mmu_irq[MAX_VDH_NUM];
} DRV_IRQ_RECORD_S;

/*ѹ������*/
typedef struct hi_VFMW_CHAN_CMP_PARA
{
    UINT32 VCmpEnable;
    UINT32 LossCmpEnable;
    UINT32 YCmpRatio;
    UINT32 UVCmpRatio;
} VFMW_CHAN_CMP_PARA_S;

/* �������������ݼ� */
typedef struct hiVFMW_CTRL_DATA_S
{
    SINT32        s32IsVCTRLOpen;   /* ��־VCTRL�Ƿ�ȫ�ִ� */
    //OSAL_TASK_MUTEX stDecMutex;
    //OSAL_EVENT    eventVdmReady;

    TASK_STATE_E  eTaskState;       /* �߳�״̬ */
    TASK_CMD_E    eTaskCommand;     /* �߳�ָ�� */

    //OSAL_TASK     hThread;          /* �߳̾�� */
    VOID *hThread;          /* �߳̾�� */

    SINT32        s32ThreadPos;    /* �߳�λ�� */

    SINT32        s32ThisChanIDPlus1;    /* ��ǰ���ڽ����﷨�����ͨ���� */
    DRV_MEM_S     stDrvMem;
    SINT32        (*event_report_vdec)(SINT32 ChanID, SINT32 type, VOID *p_args );
    SINT32        (*event_report_omxvdec)(SINT32 ChanID, SINT32 type, VOID *p_args );
    DRV_IRQ_RECORD_S stIrqRecord;
} VFMW_CTRL_DATA_S;

typedef struct hiVFMW_CHAN_FRM_BUF_S
{
    MEM_RECORD_S stFrameBuffer;
    UINT8 u8BufferNodeState; //0:Ԥ����õ��Ľڵ�, 1:��̬����õ��Ľڵ�,0xFF:���нڵ�
} VFMW_CHAN_FRM_BUF_S;
/* ����ͨ���ڴ��¼ */
typedef struct hiVFMW_CHAN_MEM_S
{
    MEM_RECORD_S        *pChanMem_vdh;             /* ָ���ͨ����֡��洢��Դ */
    MEM_RECORD_S        *pChanMem_scd;             /* ָ���ͨ����SCD�洢��Դ */
    MEM_RECORD_S        *pChanMem_ctx;             /* ָ���ͨ���������Ĵ洢��Դ */
    FRAME_BUF_S         *pChanMem_frm;             /* ָ���ͨ��֡��洢��Դ*/

    UINT32               u32DynamicAllocEn;        /* �Ƿ�Ϊ��̬֡�淽ʽl00273086*/
    SINT32               s32SelfAllocChanMem_vdh;  /* ��ʶͨ�� vdh �Ƿ����Լ�����ģ�1: �Լ�����, 0: �ⲿ���� */
    SINT32               s32SelfAllocChanMem_scd;  /* ��ʶͨ�� scd �Ƿ����Լ�����ģ�1: �Լ�����, 0: �ⲿ���� */
    SINT32               s32SelfAllocChanMem_ctx;  /* ��ʶͨ�� ctx �Ƿ����Լ�����ģ�1: �Լ�����, 0: �ⲿ���� */
    SINT32               s32SelfAllocChanMem_rpu;  /* ��ʶͨ�� HDR metadata �Ƿ����Լ�����ģ�1: �Լ�����, 0: �ⲿ���� */
} VFMW_CHAN_MEM_S;
typedef struct hiVFMW_MEM_ARRANGE_INFO_S
{
    VDMHAL_MEM_ARRANGE_S stMemArrange;
    SINT32 ImgSlotLen;
    SINT32 PmvSlotLen;
    SINT32 ExpectImgLen;
    SINT32 HdrMetadataLen;
} VFMW_MEM_ARRANGE_INFO_S;

typedef struct hiVFMW_DYNAMIC_FS_TIMESTAMP_S
{
    UINT32 u32StartTime;
    UINT32 u32PreEndTime;
    UINT32 u32MMZEndTime;
    UINT32 u32PreAllocTime;
    UINT32 u32MMZAllocTime;
    UINT32 u32AllTime;
} VFMW_DYNAMIC_FS_TIMESTAMP_S;

/* ����ͨ�� */
typedef struct hiVFMW_CHAN_S
{
    SINT32         s32ChanID;       /* ͨ��ID */
    SINT32         s32IsOpen;       /* 0: δ�򿪣�1: �� */
    SINT32         s32IsRun;        /* 0: ��������, 1: ���У��ɱ�����  */
#ifdef VFMW_VPSS_BYPASS_EN
    SINT32         s32IsImgOutputEn; /*0: Image �����ʹ�ܣ�1:Image ���ʹ��*/
#endif
    SINT32         s32IsInit;       /* 0: ��������״̬, 1: �ճ�ʼ����δ����*/
    SINT32         s32Priority;     /* ���ȼ���0��������ȼ�(�Ӳ�����) ~ 255(������ȼ��������ȵ���) */
    SINT32         s32StopSyntax;  /* ͣ��syntax���룬������stopͨ����ʱ����ͣ���Σ��������������У���������
                                        ��DecParam���ĸɾ����Ӷ�ʵ�ְ�ȫ��ͨ��stop��reset���� */
    SINT32         MatchVdhIdPlus1;  //��¼��ǰͨ��ƥ���Vdhid +1; -1->��ͨ��DSP������δ���������ܴ���0->���ʹ��VDH���룻1->�̶�ѡ��VDH0���룻2->�̶�ѡ��VDH1����...;
    VDEC_ADAPTER_TYPE_E   eAdapterType;   /* ָʾ��ͨ������vdec/omxvdec���� */
    VDEC_CHAN_CAP_LEVEL_E eChanCapLevel;  /* ͨ������������ */
    UINT32         u32timeLastDecParamReady;

    VDEC_CHAN_CFG_S stChanCfg;       /* �����û����ã����ڲ�ѯ�ӿ�ʵ�� */
    STREAM_INTF_S  stStreamIntf;     /* �����ӿ� */
    IMAGE_INTF_S   stImageIntf;      /* ͼ��ӿ� */
    FRAME_INTF_S   stFrameIntf;

    SINT32         s32SCDInstID;     /* ��ͨ����Ӧ��SCDʵ��ID */
    SINT32         s32VDMInstID;     /* ��ͨ����Ӧ��VDMʵ��ID */
    MEM_RECORD_S   stChanMem_vdh;       /* ��ͨ����֡��洢��Դ */
    MEM_RECORD_S   stChanMem_scd;       /* ��ͨ����SCD�洢��Դ */
    MEM_RECORD_S   stChanMem_ctx;       /* ��ͨ���������Ĵ洢��Դ */

    SINT32         s32SelfAllocChanMem_vdh;  /* ��ʶͨ�� vdh �Ƿ����Լ�����ģ�1: �Լ�����, 0: �ⲿ���� */
    SINT32         s32SelfAllocChanMem_scd;  /* ��ʶͨ�� scd �Ƿ����Լ�����ģ�1: �Լ�����, 0: �ⲿ���� */
    SINT32         s32SelfAllocChanMem_ctx;  /* ��ʶͨ�� ctx �Ƿ����Լ�����ģ�1: �Լ�����, 0: �ⲿ���� */
    SINT32         s32SelfAllocChanMem_rpu;  /* ��ʶͨ�� HDR metadata �Ƿ����Լ�����ģ�1: �Լ�����, 0: �ⲿ���� */
    UADDR          s32VdmChanMemAddr;
    SINT32         s32VdmChanMemSize;    /* VDMͨ����ռ�ݵĴ洢�ռ��С */
    UADDR          s32ScdChanMemAddr;
    UADDR          s32SdecMemAddr;       /* �������ʹ�õĴ洢�ռ䣬ΪDNR+VDM�Ŀռ� */
    SINT32         s32SdecMemSize;
    SINT32         s32ScdChanMemSize;    /* SCDͨ����ռ�ݵĴ洢�ռ��С */

    UADDR          s32BpdChanMemAddr;
    SINT32         s32BpdChanMemSize;    /* BPDͨ����ռ�ݵĴ洢�ռ��С */

    UADDR          s32Vp8SegIdChanMemAddr;
    SINT32         s32Vp8SegIdChanMemSize;    /* SegIdͨ����ռ�ݵĴ洢�ռ��С */

    UADDR          s32Vp9SegIdChanMemAddr;
    SINT32         s32Vp9SegIdChanMemSize;    /* SegIdͨ����ռ�ݵĴ洢�ռ��С */

    IMAGE_FORMAT   stRecentImgformat;
    FRAME_PACKING_TYPE_E  stRecentImgPackingType;

    SINT32         s32NoStreamFlag; /* ���ڸ�ͨ��û���㹻��������δ�����ɽ������decparam */
    SINT32         s32LastFrameIdPlus2;  /* ���һ֡���ʱ�����ڼ�¼���һ֡��image_id + 2 ��1D ת2Dʱ������BTL/DNR���õ�*/
    LAST_FRAME_STATE_E eLastFrameState;  /* �������һ֡��ǵ�״̬ */

    SINT32         s32CountNoDecparamFlag; /* ����û�н��������ʼ��ʱ��־ */
    UINT32         u32NoDecparamStartTime;

    /* �û�̬������Ҫ��VDM memory��֡ӳ����ȥ. ����ʱ�γɷָ������Ϣ��¼֡��ķָ��ʹ��״�� */
    UADDR          s32UsrdecFramePhyAddr[MAX_USRDEC_FRAME_NUM];
    SINT32         s32UsrdecFrameSize;
    SINT32         s32UsrdecFrameNum;
    USRDEC_FRAME_DESC_S  stRecentUsrdecFrame;

    VID_STD_E      eVidStd;

    SYNTAX_EXTRA_DATA_S stSynExtraData;
    SINT32   s32FrameRate;
    CHAN_DEC_CORE_E eDecCore;
    SM_INSTANCE_S   SmInstArray;
    FSP_INST_S      FspInst;
    SINT32 AllocFrameOnly;

    SINT32 s32CurFsSize;
    SINT32 s32RefNum;
    SINT32 s32NeededFrameNum;//��¼vdec���ø�vfmw���ܹ���֡�����
    SINT32 s32PreAllocFrmNum;
    SINT32 s32MMZFrmNum;
    SINT32 s32RefNumChanged;
    SINT32 s32SendStreamAgainFlag;
    FRAME_BUF_S stFrmBuf[MAX_FRAME_NUM];
    VFMW_MEM_ARRANGE_INFO_S stMemArrangeInfo;
    VFMW_DYNAMIC_FS_TIMESTAMP_S stDynamicFSTimestamp;

    UINT32 CfgFrameNum;
    UINT32 isFilledMemArrnageInfo;//

#ifdef VFMW_VPSS_BYPASS_EN   //specialFrameExist->specialFrameNum
    VFMW_SPECIAL_FRAME_REC_S specialFrmRec[VFMW_MAX_RESERVE_NUM + 1];
    UINT32 specialFrameNum;//specialFrameExist;
#else
    UADDR  specialFramePhyAddr;
    UINT64 specialFrameVirAddr;
    UINT8  specialFrameNodeStatus;
    UINT32 specialFrameSize;
    UINT32 specialFrameExist;
#endif

    SINT32 resolutionChanged;
    SINT8  isMiracastChan;
    UINT32 u32DynamicFrameStoreAllocEn;
    UINT32 u32CurSavePicBitDepth;
    UADDR  ChanUniquelyID;
    SINT32 s32H264Score;
    SINT32 s32Mpeg2Score;
    SINT32 s32FindStartCodeCnt;
    SINT32 s32LastTwoStartCode;
    SINT32 s32LastOneStartCode;
    SINT32 s32CurrentStartCode;
    SINT32 s32ScdInputMmuEn;
    UINT32 DecodeFrameNumber;
    UINT32 OutputFrameNumber;
    HI_BOOL AndroidTest;
    SYNTAX_CTX_S   stSynCtx;//�˳�Ա����������һ������,����ͨ��ʱ��ʹmvc support���������õ�����������mvc��صģ��ýṹ���ڴ�Ҳֻ����δ��CTX���裬�Դﵽ�ڴ�ü�Ŀ�ġ�

} VFMW_CHAN_S;

/* �̵߳�״̬ */
typedef enum hiDSPSTATE_E
{
    DSP_STATE_NORMAL = 0,      /* DSP ��û�м����κδ���  */
    DSP_STATE_SCDLOWDLY,       /* DSP �Ѿ�������SCD���ӵĴ��룬˵������һ��ͨ�����ڵ��ӳ�ģʽ */
    DSP_STATE_AVS,             /* DSP �Ѿ�������AVS+�Ĵ��룬˵������һ��ͨ��������AVSЭ�� */
    DSP_STATE_BUTT
} DSP_STATE_E;

/*======================================================================*/
/*  ȫ�ֱ���                                                            */
/*======================================================================*/
extern VFMW_CHAN_STAT_S g_VfmwChanStat[MAX_CHAN_NUM];
extern VFMW_GLOBAL_STAT_S g_VfmwGlobalStat[MAX_VDH_NUM];
extern SINT32 g_VdmCharacter;
extern VDM_VERSION_E g_eVdmVersion;
extern SINT32  (*AcceleratorCharacter)(DECPARAM_INF_S *pDecParamInfo);

/*======================================================================*/
/*  ��������                                                            */
/*======================================================================*/
SINT32 VCTRL_SetCallBack(VDEC_ADAPTER_TYPE_E eType, SINT32 (*event_report)(SINT32 ChanID, SINT32 type, VOID *p_args));
SINT32 VCTRL_OpenVfmw(VDEC_OPERATION_S *pArgs);
SINT32 VCTRL_StopTask(VOID);
SINT32 VCTRL_StartTask(VOID);
SINT32 VCTRL_CloseVfmw(VOID);
VOID   VCTRL_Suspend(VOID);
VOID   VCTRL_Resume(VOID);
SINT32 VCTRL_CreateChan(VDEC_CHAN_CAP_LEVEL_E eCapLevel, VDEC_CHAN_OPTION_S *pChanOption, SINT32 flag, SINT32 OneChanMemFlag);
SINT32 VCTRL_DestroyChan(SINT32 ChanID);
SINT32 VCTRL_StartChan(SINT32 ChanID);
SINT32 VCTRL_StopChan(SINT32 ChanID);
SINT32 VCTRL_StopChanWithCheck(SINT32 ChanID);
SINT32 VCTRL_GetChanCfg(SINT32 ChanID, VDEC_CHAN_CFG_S *pstCfg);
SINT32 VCTRL_CmpConfigParameter(SINT32 ChanID, VDEC_CHAN_CFG_S *pstCfg);
SINT32 VCTRL_ConfigChan(SINT32 ChanID, VDEC_CHAN_CFG_S *pstCfg);
SINT32 VCTRL_ResetChanWithOption(SINT32 ChanID, VDEC_CHAN_RESET_OPTION_S *pOption);
SINT32 VCTRL_ReleaseStream(SINT32 ChanID);
SINT32 VCTRL_ResetChan(SINT32 ChanID);
VOID   VCTRL_GetChanState(SINT32 ChanID, VDEC_CHAN_STATE_S *pstChanState);
SINT32 VCTRL_SetSendStreamAgainFlag( SINT32 ChanID, SINT32 flag);
SINT32 VCTRL_GetSendStreamAgainFlag( SINT32 ChanID);
SINT32 VCTRL_SetStreamInterface( SINT32 ChanID, VOID *pstStreamIntf );
STREAM_INTF_S *VCTRL_GetStreamInterface(SINT32 ChanID);
SINT32 VCTRL_SetFrameInterface( SINT32 ChanID, FRAME_INTF_S *pstFrameIntf );
FRAME_INTF_S *VCTRL_GetFrameInterface( SINT32 ChanID);

VOID  *VCTRL_GetSyntaxCtx(SINT32 ChanID);
IMAGE_INTF_S *VCTRL_GetImageInterface(SINT32 ChanID);
SINT32 VCTRL_GetChanMemSize(VDEC_CHAN_CAP_LEVEL_E eCapLevel, VDEC_CHAN_OPTION_S *pChanOption, DETAIL_MEM_SIZE *pDetailMemSize, SINT32 flag);
VOID   VCTRL_GetChanCtxSize(VDEC_CHAN_CAP_LEVEL_E eCapLevel, SINT32 *s32ChanCtxSize);
SINT32 VCTRL_GetStreamSize(SINT32 ChanID, SINT32 *pArgs);
SINT32 VCTRL_SetDiscardPicParam(SINT32 ChanID, VDEC_DISPIC_PARAM_S *pArgs);    //add 2012.11.20
UINT32 VCTRL_ArrangeMem(SINT32 ChanID, SINT32 MaxWidth, SINT32 MaxHeight, UADDR MemAddr, SINT32 MemSize);

#ifdef VFMW_USER_SUPPORT
SINT32 VCTRL_GetUsrdecFrame(SINT32 ChanID, USRDEC_FRAME_DESC_S *pUsrdecFrame);
SINT32 VCTRL_PutUsrdecFrame(SINT32 ChanID, USRDEC_FRAME_DESC_S *pUsrdecFrame);
SINT32 USERDEC_Init(USER_CTX_S *pCtx, SYNTAX_EXTRA_DATA_S *pstExtraData);
SINT32 USERDEC_RecycleImage(USER_CTX_S *pCtx, UINT32 ImgID);
SINT32 VDH_PutUsrdecFrame(SINT32 ChanID, USRDEC_FRAME_DESC_S *pstUsrdecFrame);
#endif

SINT32 VCTRL_ChanDecparamInValidFlag(SINT32 ChanId);

VID_STD_E VCTRL_GetVidStd(SINT32 ChanId);
VOID VCTRL_GetHDRConfigInfo(SINT32 ChanId, HDR_INPUT_S *pstHDRInput);
VOID  *VCTRL_GetDecParam(SINT32 ChanId);
VOID   VCTRL_VdmPostProc( SINT32 ChanId, SINT32 ErrRatio, LUMA_INFO_S *pLumaInfo, SINT32 VdhId);
#if defined(VFMW_H264_SED_ONLY_SUPPORT) || defined(VFMW_HEVC_SED_ONLY_SUPPORT)
SINT32 VCTRL_CheckFreshRaw(SINT32 ChanID);
SINT32 VCTRL_CheckFreshSeg(SINT32 ChanID);
VOID VCTRL_VdmProcSedOnly( SINT32 ChanId, SINT32 VdhId );
UINT8 VCTRL_IsSedOnlyMode(VID_STD_E VidStd, VOID *pDecParam);
#endif
SINT32 VCTRL_GetChanImage( SINT32 ChanID, IMAGE *pImage );
SINT32 VCTRL_ReleaseChanImage( SINT32 ChanID, IMAGE *pImage );

SINT32 VCTRL_RunProcess(VOID);
VOID   VCTRL_InformVdmFree(SINT32 ChanID);
VOID   VCTRL_ExtraWakeUpThread(VOID);
SINT32 VCTRL_FlushDecoder(SINT32 ChanID);
SINT32 VCTRL_GetImageBuffer( SINT32 ChanId );
SINT32 VCTRL_GetChanIDByCtx(VOID *pCtx);
SINT32 VCTRL_GetChanIDByMemAddr(UADDR PhyAddr);
SINT32 VCTRL_IsChanDecable( SINT32 ChanID );
SINT32 VCTRL_IsChanSegEnough( SINT32 ChanID );
SINT32 VCTRL_IsChanActive( SINT32 ChanID );
VOID VCTRL_GetChanImgNum( SINT32 ChanID, SINT32 *pRefImgNum, SINT32 *pReadImgNum, SINT32 *pNewImgNum );
VDEC_CHAN_CAP_LEVEL_E  VCTRL_GetChanCapLevel(SINT32 ChanID);

#ifdef VFMW_H263_SUPPORT
SINT32 VCTRL_RegisterSoftDecoder(iMediaSDEC_FUNC_S *pstSdecFunc);
VOID   VCTRL_UnRegisterSoftDecoder(VOID);
#endif

SINT32 VCTRL_SetMoreGapEnable(SINT32 ChanID, SINT32 MoreGapEnable);

SINT32 VCTRL_SeekPts(SINT32 ChanID, UINT64 *pArgs);

#if defined(VFMW_AVSPLUS_SUPPORT)
SINT32 VCTRL_LoadDspCode(SINT32 ChanID);
SINT32 VCTRL_ReloadDspCode(SINT32 ChanID);
#endif

SINT32 VCTRL_ConfigFFFBSpeed(SINT32 ChanID, SINT32 *pArgs);
SINT32 VCTRL_ConfigPVRInfo(SINT32 ChanID, VFMW_CONTROLINFO_S *pArgs);

SINT32 VCTRL_SetDbgOption ( UINT32 opt, UINT8 *p_args );

SINT32 VCTRL_GetChanWidth(SINT32 ChanID);
SINT32 VCTRL_GetChanHeight(SINT32 ChanID);
VOID   VCTRL_SetVdecExtra(SINT32 new_extra_ref, SINT32 new_extra_disp);

SINT32 VCTRL_GetLastFrameIdPlus2(SINT32 ChanID);
VOID   VCTRL_SetLastFrameIdPlus2(SINT32 ChanID, SINT32 Value);
VOID VCTRL_SetLastFrameState(SINT32 ChanID, LAST_FRAME_STATE_E eState);

SINT32 VCTRL_OutputLastFrame(SINT32 ChanId);
VOID   VCTRL_SvdecLastFrame(SINT32 ChanId, UINT32 LastFrameID);

UINT32 VCTRL_GetImageWidth(SINT32 ChanId);
UINT32 VCTRL_GetImageHeight(SINT32 ChanId);

SINT32 VCTRL_RequestChanMem(SINT32 ChanID);
SINT32 VCTRL_GetCurChanFsSize(SINT32 ChanID);
SINT32 VCTRT_SetChanCtrlState(SINT32 ChanID, VFMW_CHANNEL_CONTROL_STATE_E ChanCtrlState);
SINT32 VCTRL_AllocMemToDecoder(SINT32 ChanID, FRAME_BUF_S *FrameBuf);

SINT32 VCTRL_SetSingleFrameBufToChan(SINT32 ChanID, FRAME_BUF_S *frameBuf);
VOID   VCTRL_SetChanFsPartitionState(SINT32 ChanID, FSP_PARTITION_STATE_E state);

VOID   VCTRL_ResetHardware(SINT32 ChanID);
VOID   VCTRL_OpenHardware(SINT32 ChanID);
VOID   VCTRL_CloseHardware(SINT32 CurChanID);
SINT32 DelAllFrameMemRecord(SINT32 ChanID, FRAME_BUF_S *pFrmBuf);

IMAGE_VO_QUEUE *VCTRL_GetChanVoQue(SINT32 ChanID);

#ifdef VFMW_VPSS_BYPASS_EN
SINT32 VCTRL_ReportOccupiedFrame(SINT32 chanID, VDEC_SPECIAL_FRM_S *pSpecialFrmInfo);
SINT32 VCTRL_ImageOutputEnable(SINT32 chanID, SINT32 *pImgOutputEn);
SINT32 VCTRL_FindOccupiedFrame(SINT32 chanID);
#endif

UINT32 VCTRL_GetFsSize(SINT32 ChanId, SINT32 Width, SINT32 Height);

VOID VCTRL_EnableEsBuf(SINT32 ChanID);
VOID VCTRL_DisableEsBuf(SINT32 ChanID);
SINT32 VCTRL_IfEsBufEnable(SINT32 ChanID);
VOID VCTRL_ClearDecparam(SINT32 ChanId);

VOID VCTRL_RecordPosTime(UINT32 pos);
VOID VCTRL_RecordData(UINT32 pos, UINT32 Data);
#endif
