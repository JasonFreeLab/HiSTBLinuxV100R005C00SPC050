#ifndef __SCD_DRV_H__
#define __SCD_DRV_H__

#include "mem_manage.h"
#include "vfmw.h"
#include "sysconfig.h"

#define SCDDRV_OK       (0)
#define SCDDRV_ERR      (-1)
#define SCD_IDLE        (0)
#define SCD_BUSY        (1)
#define HEADER_BUFFER_SIZE         (128)

#ifdef CFG_SCD_TIME_OUT
#define SCD_TIMEOUT     (CFG_SCD_TIME_OUT)
#else
#define SCD_TIMEOUT     (20000)
#endif

#ifdef CFG_SCD_BUF
#define SCD_MSG_BUFFER  (CFG_SCD_BUF)
#else
#define SCD_MSG_BUFFER  (700*1024)  // 低延迟所需部分空间在这里一起分配
#endif

extern UADDR  s_ScdRegPhyBaseAddr[MAX_SCD_NUM];
extern UADDR  s_ScdRegResetPhyAddr[MAX_SCD_NUM];
extern UADDR  s_ScdRegResetOKPhyAddr[MAX_SCD_NUM];

#define  WR_SCDREG(id,reg,dat)   MEM_WritePhyWord((s_ScdRegPhyBaseAddr[id] + reg),(dat))
#define  RD_SCDREG(id,reg)       MEM_ReadPhyWord((s_ScdRegPhyBaseAddr[id] + reg))

typedef enum
{
    FMW_OK          = 0,
    FMW_ERR_PARAM   = -1,
    FMW_ERR_NOMEM   = -2,
    FMW_ERR_NOTRDY  = -3,
    FMW_ERR_BUSY    = -4,
    FMW_ERR_RAWNULL = -5, // Number or Size is 0
    FMW_ERR_SEGFULL = -6, // Number or Size is 0
    FMW_ERR_SCD     = -7
} FMW_RETVAL_E;

typedef enum
{
    SCDDRV_SLEEP_STAGE_NONE = 0,      // 未休眠
    SCDDRV_SLEEP_STAGE_PREPARE,       // 收到休眠命令，但还未完成休眠
    SCDDRV_SLEEP_STAGE_SLEEP,         // 已休眠
    SCDDRV_SLEEP_STAGE_BUTT
} SCDDRV_SLEEP_STAGE_E;

/* control registers */
#define  REG_SCD_START        0x800
#define  REG_LIST_ADDRESS     0x804
#define  REG_UP_ADDRESS       0x808
#define  REG_UP_LEN           0x80c
#define  REG_BUFFER_FIRST     0x810
#define  REG_BUFFER_LAST      0x814
#define  REG_BUFFER_INI       0x818
#define  REG_SCD_INT_MASK     0x81c
#define  REG_SCD_PROTOCOL     0x820
#define  REG_SCD_INI_CLR      0x824
/* state registers */
#define  REG_SCD_OVER         0x840

#define REG_PREVIOUS_BYTE_LSB      0x83c
#define REG_PREVIOUS_BYTE_MSB     0x844

#define  REG_SCD_NUM          0x84c
#define  REG_ROLL_ADDR        0x850
#define  REG_SRC_EATEN        0x854

#define REG_SEG_BUFFER_OFFSET    0x858
#define REG_SEG_NEXT_ADDR     0x85c

#define  REG_DSP_SPS_MSG_ADDRESS      0x828
#define  REG_DSP_PPS_MSG_ADDRESS      0x82c
#define  REG_DVM_MSG_ADDRESS           0x830
#define  REG_SED_TOP_ADDRESS           0x834
#define  REG_CA_MN_ADDRESS             0x838

#define  REG_SCD_CLK_CFG      0x880

#define  REG_AVS_FLAG       0x0000
#define  REG_EMAR_ID        0x0004
#define  REG_VDH_SELRST        0x0008
#define  REG_VDH_ARBIT_CTRL_STATE             0X0010
#define  REG_VDH_CK_GT       0x000c
#define  REG_DSP_WATCH_DOG             0X0018

// 实例状态
#define SM_INST_MODE_IDLE   0
#define SM_INST_MODE_WORK   1
#define SM_INST_MODE_WAIT   2

// 极限常数
#ifdef CFG_MAX_RAW_NUM
#define MAX_STREAM_RAW_NUM  CFG_MAX_RAW_NUM
#else
#define MAX_STREAM_RAW_NUM  (1024)
#endif

#ifdef CFG_MAX_SEG_NUM
#define MAX_STREAM_SEG_NUM  CFG_MAX_SEG_NUM
#else
#define MAX_STREAM_SEG_NUM  (4096)
#endif

#define MAX_STREAM_SEG_ALLOW    (100000)
#define MIN_STREAM_SEG_NUM      4  //最小启动SCD的消息池的个数
#define SM_SCD_UP_INFO_NUM      2
#ifdef SCD_MP4_SLICE_ENABLE
#define MAX_SM_SCD_UP_INFO_NUM  3  //MPEG4上行消息区使用3个word，其他协议使用2个word，取最大的
#else
#define MAX_SM_SCD_UP_INFO_NUM  SM_SCD_UP_INFO_NUM
#endif
#define SM_MAX_DOWNMSG_SIZE     (3*MAX_STREAM_RAW_NUM*sizeof(SINT32))
#define SM_MAX_UPMSG_SIZE       (SM_SCD_UP_INFO_NUM*MAX_STREAM_SEG_NUM*sizeof(SINT32))

#define DSP_SPS_MSG_SIZE        (32*8*4)
#define DSP_PPS_MSG_SIZE        (256*8*4)
#define DVM_SIZE                (2*64*4)
#define DSP_SED_TOP_SIZE        (64*4*1088)
#define CA_MN_SIZE              (64*4*1088)

#define SM_SEGWASTE_BUF_SIZE  64     //Seg剩余空间浪费的大小

//#define MIN_BTM_SEG_LEN  (2*1024)  // 要求WORD整数倍, 用来拷贝卷绕的,现在用FPGA_SCD_SEG_BLANK_AHB_LEN
#define MIN_TOP_SEG_LEN  (1*1024)    // 要求WORD整数倍，可能解冒的
#define SM_H263_THRESHOLD_NUM 30     //连续多少个H263头出现后就算成H263模式

#define SM_RAW_DISCARD_SIZE    (1024*1024)

#define WAIT_SEG_REL_MAX_TIME   1000
#define WAIT_SCD_RDY_MAX_TIME   1000

#define SM_VIDOBJLAY_START_CODE        0x00000120
#define SM_VOP_START_CODE              0x000001b6
#define SM_SHORT_VIDEO_START_CODE      0x00008000

#define SEG_CUT_NORMAL   0
#define SEG_CUT_REPEAT   1
#define SEG_CUT_HALF     2

#define SMSEG_STATE_INVALID   0
#define SMSEG_STATE_FRESH     1
#define SMSEG_STATE_READOUT   2

#define SMSEG_IS_READ( seg )     (((seg).SegState == SMSEG_STATE_READOUT) ? 1 : 0)
#define SMSEG_IS_RELEASED( seg ) (((seg).SegState == SMSEG_STATE_INVALID) ? 1 : 0)
#define SMSEG_IS_FRESH( seg )    (((seg).SegState == SMSEG_STATE_FRESH) ? 1 : 0)

#define SMSEG_SET_ISREAD( seg )                       \
    do{                                     \
        (seg).SegState = SMSEG_STATE_READOUT;                             \
    } while (0)

#define SMSEG_SET_ISRELEASED( seg )                     \
    do{                                     \
        (seg).SegState = SMSEG_STATE_INVALID;                             \
    } while (0)

#define SMSEG_SET_ISFRESH( seg )                      \
    do{                                     \
        (seg).SegState = SMSEG_STATE_FRESH;                             \
    } while (0)

#define FMW_ASSERT( cond )                          \
    do{                                     \
        if( !(cond) )                             \
        {                                   \
            return;                               \
        }                                   \
    } while (0)

#define FMW_ASSERT_RET(cond, ret)                     \
    do{                                     \
        if (!(cond))                             \
        {                                   \
            return (ret);                           \
        }                                   \
    } while (0)

#define SMSEG_PHY2VIR(SegArrayPtr, phy, vir)                \
    do{                                     \
        (vir) = SegArrayPtr->pSegBufVirAddr + ((phy) - SegArrayPtr->SegBufPhyAddr); \
    } while (0)


typedef enum
{
    INITIALISE = 0,
    WRITE_DOWN_MSG = 1,
    IN_ISR = 2,
    SEEK_PTS = 3
} PUSH_RAW_OVER_STATE;

typedef struct
{
    STREAM_DATA_S RawPacket[MAX_STREAM_RAW_NUM];
    SINT32      Head;
    SINT32      Tail;
    SINT32      History;
    SINT32      FirstPacketOffset;
    SINT32      CurShowIndex;
    SINT32      RawTotalSize;
} RAW_ARRAY_S;

typedef struct
{
    SINT8    ScdIntMask;
    UINT8    SliceCheckFlag;
    SINT8    ScdStart;
    UADDR    DownMsgPhyAddr;
    SINT32   *pDownMsgVirAddr;
    SINT32   *pUpMsgVirAddr;
    UADDR    UpMsgPhyAddr;
    SINT32   UpLen;
    UADDR    BufferFirst;
    UADDR    BufferLast;
    UADDR    BufferIni;
    UINT32   ScdProtocol;
    SINT32   ScdIniClr;
    UINT32   ScdLowdlyEnable;
    UINT32   ScdMmuEn;
    UINT32   VdhMmuEn;
    UINT32   ScdInputMmuEn;
    SINT32   reg_avs_flag;
} SM_CTRLREG_S;

typedef struct
{
    SINT32  Avs_Flag;
    SINT32  EMAR_ID;
    SINT32  VDH_SEL_RST_EN;
} GLB_CTRLREG_S;
typedef struct
{
    SINT32  Scdover;
    SINT32  ScdInt;
    SINT32  ShortScdNum;
    UINT32  StartCodeNum;
    UADDR   ScdRollAddr;
    SINT32  SrcEaten;
    UINT32  UpMsgLenInWord;
    UADDR  seg_next_addr;
} SM_STATEREG_S;

/* MEPG4 特有的有效上行消息 */
typedef struct
{
    USIGN  IsShStreamFlag:        1;
    USIGN  SliceFlag:             1;
    USIGN  IsShortHeader:         1;
    USIGN  StartCodeBitOffset:    4;
    USIGN  StartCodeLength:       4;
    USIGN  Reserved:              21;
} MP4_SCD_UPMSG;

typedef struct
{
    UINT8     *VirAddr;
    SINT8     SegState;
    SINT8     CutResult;
    UINT8     IsLastSeg;
    UINT8     IsStreamEnd;
    UINT8     DspCheckPicOverFlag;
    UADDR     PhyAddr;
    UINT32    LenInByte;
    SINT32    StreamID;
    UINT64    Pts;
    UINT64    RawPts;
    UINT64    Usertag;
    UINT64    DispTime;
    UINT32    DispEnableFlag;
    UINT32    DispFrameDistance;
    UINT32    DistanceBeforeFirstFrame;
    UINT32    GopNum;
    /* MEPG4 特有的有效上行消息 */
    MP4_SCD_UPMSG stMp4UpMsg;
} STREAM_SEG_S;


/********************************************************************************

RawPacket 原始码流信息的记录空间，最大可记录MAX_RAW_PACKET_NUM个码流包的信息。
Head    第一个有效记录的位置
Tail    最后一个有效记录的位置
SegBufPhyAddr 码流片段缓冲区物理地址
pSegBufVirAddr  码流片段缓冲区虚拟地址
SegBufSize    码流片段缓冲区大小，单位：字节
SegBufReadAddr  码流片段缓冲区的读地址
SegBufWriteAddr 码流片段缓冲区的写地址
*********************************************************************************/
typedef struct
{
    UINT8         *pSegBufVirAddr;
    STREAM_SEG_S  StreamSeg[MAX_STREAM_SEG_NUM];
    SINT32        Head;
    SINT32        Tail;
    SINT32        History;
    SINT32        Current;
    UADDR         SegBufPhyAddr;
    SINT32        SegBufSize;
    UADDR         SegBufReadAddr;
    UADDR         SegBufWriteAddr;

    SINT32        SegTotalSize;    /* SegTotalSize:  Insert加, Release减 */
    SINT32        SegFreshSize;    /* SegFreshSize:  Insert加, Read减 */
    SINT32        SegFreshNum;
} SEG_ARRAY_S;


/********************************************************************************
Mode  指定配置后SM实例的工作模式。
        0：非工作模式
        1：工作模式
        如果Mode＝0表明外部模块希望这个SM实例停止工作，这种情况下只需关闭此实例，其它成员的取值被忽略。
Priority    优先级
            优先级通常是一个大于零的整数，数值越大优先级越高。
            0代表"无权限"，即无优先级，任何时候都不会被调度。
VidStd  VID_STD_E 视频协议类型。由于视频协议的多样性，在码流切分和管理中可能存在与协议相关的操作，这个参数指定协议类型。
DownMsgAddr 下行消息（码流链）的物理地址
DownMsgSize 下行消息的大小（字节数）
UpMsgAddr   上行消息（起始码地址集）的物理地址
UpMsgSize   上行消息的大小（字节数）
SegBufAddr  码流缓冲区的物理地址。这个缓冲区中存放的是被SCD（或其它等效模块）切割好的码流。缓冲区地址分为物理地址和虚拟地址，是为了适应某些操作系统（比如Linux）的特点，在其它操作系统中，虚拟地址和物理地址被置成同一个值即可。
SegBufSize  缓冲区的大小，以字节为单位。
*********************************************************************************/
typedef struct
{
    UINT8        *pBufVirAddr;
    UINT8         Priority;
    VID_STD_E     VidStd;

    UADDR         BufPhyAddr;
    SINT32        BufSize;
    UADDR         RegPhyBaseAddr;
    STD_EXTENSION_U    StdExt;              /* 扩展信息，VC1相关的是码流是否为AP 和版本信息*/
    SINT32        ScdLowdlyEnable;          /* 0: 低延迟未使能; 1: 低延迟使能 */
    SINT32        SedOnlyEnable;
    SINT32        s32ChanLowlyEnable;
    SINT32        IsOmxPath;                /* 0: 低缓存未使能; 1: 低缓存使能 */
    SINT32        MaxRawPacketNum;
    SINT32        MaxRawPacketSize;
    SINT32        s32ScdMmuEn;
    SINT32        s32VdhMmuEn;
} SM_CFG_S;

typedef struct
{
    UINT8        *pSegBufVirAddr;
    UINT32       *pDownMsgVirAddr;
    SINT32        DownMsgSize;
    UADDR         DownMsgPhyAddr;
    UINT32        *pUpMsgVirAddr;
    UADDR         UpMsgPhyAddr;
    SINT32        UpMsgSize;
    SINT32        UpMsgNum;
    UADDR         SegBufPhyAddr;
    SINT32        SegBufSize;
} SM_BUFFERCFG_S;

typedef struct
{
    SINT8         InstMode;        /* 0: 非工作模式,  1: 工作模式   */
    SINT32        RawNum;          /* 原始码流包数目                */
    SINT32        SegNum;          /* 原始码流数据总量              */
    SINT32        TotalRawSize;    /* 已切割的码流片段数目          */
    SINT32        TotalSegSize;    /* 已切割的码流片段数据总量      */
    SINT32        numReadSegFail;  /* 连续读不到seg的计数           */
} SM_INST_INFO_S;

typedef struct
{
    UINT8    *pCurrStartVirAddr;
    UINT8    *pCurrEndVirAddr;
    UADDR     CurrStartPhyAddr;
    UADDR     CurrEndPhyAddr;
    SINT32    Length;
    SINT32    TotalLen;
    UINT64    Pts;
} SM_PUSHRAWPACKET_S;

typedef struct
{
    SINT32  PushRawNum;
    SINT32  PushRawTotalLen;
    PUSH_RAW_OVER_STATE PushRawOverState;
} SM_PUSHRAW_S;

typedef enum
{
    SM_NOT_MPEG4 = 0,
    SM_MPEG4_NOTH263,
    SM_MPEG4_H263
} MPEG4_SUB_STD;

typedef struct
{
    UINT8    *pSegBufVirAddr; //Seg Buffer的虚拟地址,取数据时使用
    UINT32   *pScdUpMsg;      //被过滤的上行消息的地址
    SINT32    ProtocolType;
    SINT32    ModeFlag;       //0:在非Mpeg4模式; 1:上一次不是H263模式, 2:上一次是H263模式
    SINT32    LastH263Num;    //上一次解码连续为H263头的数量
    UADDR     SegBufPhyAddr;
    SINT32    SegBufSize;
    UADDR     SegBufRollAddr;
    SINT32    SegNum;         //被过滤的SegStream共有多少包
    SINT32    SMInstID;       //当前包的实例ID
} SM_SEGSTREAMFILTER_S;

typedef struct
{
    SINT8          SegFullFlag;
    SINT8          IsCounting;
    SINT8          LastCfgAllRawFlag; // 1 : 该实例上次启动SCD时对所有的RAW码流都进行了配置处理，该标志位在每次SCD启动时进行判断赋值
    SINT8          FillNewRawFlag;    // 1 : 该实例上次SCD处理后又有新的RAW码流，该标志位会在每次SCD启动后清0
    VBOOL          IsSegBypass;
    SM_CFG_S       Config;
    RAW_ARRAY_S    RawPacketArray;
    SEG_ARRAY_S    StreamSegArray;
    SM_PUSHRAW_S   SmPushRaw;
    SM_BUFFERCFG_S BufAddrCfg;
    SINT32         InstID;
    SINT32         ScdID;            //记录当前通道被处理的SCD id号，用于SM_Stop等函数中,在启动SCD切割钱要重新赋值
    SINT32         CutingFlag;       //记录当前通道是否正在被SCD切割，在SM_SCDIntServeProc中断处理函数中清0，在CutStreamWithSCD中置1
    SINT32         MatchScdIdPlus1;  //记录当前通道匹配的SCDid +1; -1->该通道DSP处理部分未就绪，不能处理；0->随机使用SCD切割；1->固定选用SCD0切割；2->固定选用SCD1切割...;
    SINT32         Mode;
    UINT32         Mpeg4ModeFlag;
    UINT32         LastH263Num;
    UINT32         BlockTimeInMs;    //被阻塞的时间，单位ms
    UINT32         LastBlockTime;    //上一次被阻塞的时间(系统时间)，用于后续刷新阻塞时间
    UINT64         LastPts;          //如果本次的Pts与上次相同则打上-1
    SINT32         PrevCfgRawSize;
    SINT32         PrevCfgSegSize;

    /* 统计码率 */
    SINT32         TotalRawSize;
    UINT32         LastStatTime;     //用于统计码率的时间
    UINT32         BitRate;          //码率, 单位Kbps

    /* 其它统计信息 */
    SINT32         numReadSegFail;
    SINT32         LastSCDStartTime; //上次启动SCD处理的时间，单位 毫秒

    UINT32         UpMsgStepInWord;
    UINT32         u32RawSizeCount;
    UINT32         u32RawNumCount;
    SINT32         s32ChanLowlyEnable;

    UINT32         HeaderLen;
    UINT8          HeaderBuf[HEADER_BUFFER_SIZE];
    SINT32         s32ScdInputMmuEn;

    UINT16         pre_scd_previous_byte_msb;
    UINT32         pre_scd_previous_byte_lsb;

    UINT16         scd_previous_byte_msb;
    UINT32         scd_previous_byte_lsb; // near to the next seg

    UADDR         seg_next_addr;

    UINT32         first_start_scd_flag;

    UADDR          last_start_code_addr;
    UINT32         last_unfinished_seg_size;

    UINT32         roll_flag;
    UADDR          roll_addr;

    STREAM_SEG_S   last_unfinished_seg;
    UINT64         raw_msg_arr[MAX_STREAM_RAW_NUM][2];
} SM_INSTANCE_S;

typedef struct hiSCD_DRV_MEM_S
{
    UADDR          HwMemAddr;
    SINT32         HwMemSize;
    UINT32        *pDownMsgMemVirAddr;
    UADDR          DownMsgMemAddr;
    SINT32         DownMsgMemSize;
    SINT32        *pUpMsgMemVirAddr;
    UADDR          UpMsgMemAddr;
    SINT32         UpMsgMemSize;
    UADDR          ScdRegAddr;
    UADDR          ScdResetRegAddr;
} SCD_DRV_MEM_S;

typedef struct
{
    SCD_DRV_MEM_S       ScdDrvMem;
    SINT32              IsScdDrvOpen;
    SINT32              ThisInstID;
    SINT32              SCDState;
    UINT32              LastProcessTime;
    SINT32              DspReloadFlag;
} SMDRV_PARAM_S;

typedef struct
{
    SM_INSTANCE_S      *pSmInstArray;
    SINT32              SmInstPriority;
} SM_IIS_S;


SINT32 ResetSCD(SINT32 ScdId);
SINT32 DeleteRawPacketInBuffer(SINT32 SmID, SINT32 ResetFlag);
SINT32 GetRawStreamSize(RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamSize);
SINT32 GetRawStreamNum(RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamNum);
SINT32 GetSegStreamSize(SEG_ARRAY_S *pSegStreamArray, SINT32 *pStreamSize);
UINT32 GetSegStreamNum(SEG_ARRAY_S *pSegStreamArray);
VOID   GetFreshSegStream(SEG_ARRAY_S *pSegStreamArray, SINT32 *pFreshNum, SINT32 *pFreshSize);
SINT32 SM_OpenSCDDrv(UADDR MemAddr, SINT32 MemSize, SINT32 ScdId);
SINT32 SM_CloseSCDDrv(SINT32 ScdId);
VOID   SM_InstInit(VOID);
VOID   SCDDRV_ResetSCD(SINT32 ChanID);
SINT32 SM_ClearInst(SINT32 SmID);
SINT32 SM_Reset(SINT32 SmID);
SINT32 SM_Start(SINT32 SmID);
SINT32 SM_Stop(SINT32 SmID);
SINT32 SM_Config(SINT32 SmID, SM_CFG_S *pSmCfg);
SINT32 SM_GetInfo(SINT32 SmID, SM_INST_INFO_S *pSmInstInfo);
SINT32 SM_ReadSegStream(SINT32 SmID, STREAM_SEG_S *pStreamSeg);
SINT32 SM_ReleaseStreamSeg(SINT32 SmID, SINT32 StreamID);
VOID   SM_SCDIntServeProc(SINT32 ScdId);
VOID   SM_Wakeup(VOID);
VOID   PrintScdRawState(SINT32 SmID, SINT32 PrintDetail);
VOID   PrintScdSegState(SINT32 SmID, SINT32 PrintDetail);
SINT32 SM_SeekPts(SINT32 ChanID, UINT64 *pArgs);
VOID   SCDDRV_LoadDspCode(SINT32 ScdId, DSP_REQUIRE_E Require);
VOID   SCDDRV_SetStateIdle(SINT32 ScdId);
SINT32 SCDDRV_IsChanDec(SINT32 SmID);
VOID   SCD_ConfigReg(UINT32 Reg, UINT32 Data, SINT32 Id, VOID *pTask);
SINT32 SCDDRV_PrepareSleep(SINT32 ScdId);
VOID   SCDDRV_ForceSleep(SINT32 ScdId);
VOID   SCDDRV_ExitSleep(SINT32 ScdId);
SCDDRV_SLEEP_STAGE_E SCDDRV_GetSleepStage(SINT32 ScdId);

#endif  // __SCD_DRV_H__

