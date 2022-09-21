
#ifndef __FSP_HEADER__
#define __FSP_HEADER__

#ifdef __cplusplus
extern "C" {
#endif

#include "public.h"
#include "vfmw.h"
#include "syn_cmn.h"


/*---------------------------- EXTERNAL MACRO --------------------------------*/
#define FSP_OK                      (0)
#define FSP_ERR                     (-1)

#define FSP_FALSE                   (0)
#define FSP_TRUE                    (1)

#define FSP_WAIT_ARRANGE            (2)

#define FS_DISP_STATE_NOT_USED      (0)
#define FS_DISP_STATE_ALLOCED       (1)
#define FS_DISP_STATE_DEC_COMPLETE  (2)
#define FS_DISP_STATE_WAIT_DISP     (3)
#define FS_DISP_STATE_OCCUPIED      (4)

#define MAX_PMV_NUM  MAX_PMV_SLOT_NUM

#define VP9_RPF_SOFT_EN

#define FSP_ASSERT_RET(cond, else_print)                            \
do {                                                                \
    if (!(cond))                                                    \
    {                                                               \
        dprint(PRN_FATAL,"fsp.c,L%d: %s\n", __LINE__, else_print ); \
        return FSP_ERR;                                             \
    }                                                               \
}while(0)

#define FSP_ASSERT(cond, else_print)                                \
do {                                                                \
    if (!(cond))                                                    \
    {                                                               \
        dprint(PRN_FATAL,"fsp.c,L%d: %s\n", __LINE__, else_print ); \
        return;                                                     \
    }                                                               \
}while(0)


/*----------------------------- EXTERNAL TYPE --------------------------------*/
typedef enum
{
    FSP_PHY_FS_TYPE_DECODE,
    FSP_PHY_FS_TYPE_DISPLAY,
    FSP_PHY_FS_TYPE_BUTT
} FSP_PHY_FS_TYPE_E;

typedef enum
{
    FSP_PHY_FS_STORE_TYPE_FRAME,
    FSP_PHY_FS_STORE_TYPE_FIELD,
    FSP_PHY_FS_STORE_TYPE_BUTT
} FSP_PHY_FS_STORE_TYPE_E;

typedef enum
{
    LFS_PMV_STATE_NOT_USE,
    LFS_PMV_STATE_ALLOCATED,
    LFS_PMV_STATE_VALID,
    LFS_PMV_STATE_BUTT
} LFS_PMV_STATE_E;

typedef enum
{
    FSP_INST_STATE_NULL,
    FSP_INST_STATE_INUSE,
    FSP_INST_STATE_BUTT
} FSP_INST_STATE_E;

typedef enum
{
    FSP_PARTITION_STATE_FIRST = 0,
    FSP_PARTITION_STATE_WAIT,
    FSP_PARTITION_STATE_SUCCESS,
    FSP_PARTITION_STATE_FAIL,
} FSP_PARTITION_STATE_E;

typedef struct hiFSP_INST_CFG_S
{
    SINT8  UserDec;
    SINT8  ExpectedDecFsNum;
    SINT8  ExpectedDispFsNum;
    SINT8  ExpectedPmvNum;
    SINT32 DecFsWidth;
    SINT32 DecFsHeight;
    SINT32 DispFsWidth;
    SINT32 DispFsHeight;
} FSP_INST_CFG_S;

typedef struct
{
    UINT8  IsAvailable;
    SINT8  IsDecRef;
    SINT8  DispState;
    SINT32 PhyFsID;
    UADDR  PhyAddr;
    UINT32 BufSize;
    UADDR  MetadataAddr;
    UADDR  LineNumAddr;
    UINT32 YStride;
    UINT32 UVStride;
    SINT32 Stride_2bit;
    SINT32 LumaOffset_2bit;
    SINT32 ChromOffset_2bit;
    SINT32 HeadStride;
    SINT32 HeadInfoSize;
    SINT32 FsWidth;
    SINT32 FsHeight;
    SINT32 ChromOffset;
    SINT32 LumaPixelOffset;
    SINT32 ChromaPixelOffset;
    UINT32 Tick;
    FSP_PHY_FS_STORE_TYPE_E eStoreType;
#ifdef VP9_RPF_SOFT_EN
    UINT32 DispCnt;
#endif
} FSP_PHY_FS_S;

typedef struct
{
    FSP_PHY_FS_S PhyFS;
    UINT32 IsValid;
} FSP_PHY_FS_RECORD_S;

typedef struct
{
    SINT8  IsRef;
    SINT8  DispState;
    SINT8  IsDummyFs;
    SINT8  LogicFsID;
    SINT8  PmvIdc;
    UADDR  PmvAddr;
    SINT32 HalfPmvOffset;
    UINT32 TR;
    UINT32 Tick;
    LFS_PMV_STATE_E eLfsPmvState;
    FSP_PHY_FS_S *pstDecodeFs;
    FSP_PHY_FS_S *pstDispOutFs;
    IMAGE stDispImg;
} FSP_LOGIC_FS_S;

typedef struct
{
    SINT8  LowBufEnable;
} FSP_ATTR_S;

typedef struct
{
    SINT8  InstID;
    SINT8  PmvNum;
    SINT8  DecFsNum;
    SINT8  DispFsNum;
    SINT32 DecFsSize;
    FSP_PHY_FS_RECORD_S stDecFsRec[MAX_FRAME_NUM];
} FSP_INST_INFO_S;

typedef struct
{
    SINT8  InstID;
    SINT8  LowBufEnable;
    SINT8  TotalValidFsNum;
    SINT8  DecFsNum;
    SINT8  DispFsNum;
    SINT8  PmvNum;
    SINT32 HalfPmvOffset;
    UINT32 InstTick;
    UINT32 CfgFrameNum;
    UINT32 CfgPmvNum;
    UINT32 CfgHdrNum;
    FSP_INST_STATE_E      eFspInstState;
    FSP_PARTITION_STATE_E eFspPartitionState;
    FSP_INST_CFG_S        stInstCfg;
    FSP_PHY_FS_RECORD_S   stDummyPhyFsRec;
    FSP_LOGIC_FS_S        stLogicFs[MAX_FRAME_NUM];
    FSP_PHY_FS_RECORD_S   stDecFsRec[MAX_FRAME_NUM];
    FSP_PHY_FS_RECORD_S   stDispFsRec[MAX_FRAME_NUM];
    PMV_RECORD_S          stPmvRec[MAX_PMV_NUM];
} FSP_INST_S;


/*----------------------------EXTERNAL FUNCTION-------------------------------*/
VOID   FSP_Init(VOID);
VOID   FSP_Exit(VOID);
SINT32 FSP_ConfigAttribute(SINT32 InstID, FSP_ATTR_S *pstAttr);
SINT32 FSP_EnableInstance(SINT32 InstID, FSP_INST_S *pFspInst);
VOID   FSP_DisableInstance(SINT32 InstID);
SINT32 FSP_ResetInstance(SINT32 InstID);
SINT32 FSP_EmptyInstance(SINT32 InstID);
SINT32 FSP_ClearNotInVoQueue(SINT32 InstID, IMAGE_VO_QUEUE *pstVoQue);
SINT32 FSP_ConfigInstance(SINT32 InstID, FSP_INST_CFG_S *pstFspInstCfg);
SINT32 FSP_ConfigFrameBuf(SINT32 InstID, UADDR MemPhyAddr, SINT32 MemSize, SINT32 *UsedMemSize);
SINT32 FSP_NewLogicFs(SINT32 InstID, SINT32 NeedPhyFs);
SINT32 FSP_RelsePhyFs(SINT32 InstID, UINT32 CurSize);
SINT32 FSP_GetPhyFsNum(SINT32 InstID, UINT32 CurSize );
VOID   FSP_ClearLogicFs(SINT32 InstID, SINT32 LogicFrameID, SINT32 HoldDispFs);
VOID   FSP_SetRef(SINT32 InstID, SINT32 LogicFrameID, SINT32 IsRef);
SINT32 FSP_GetRef(SINT32 InstID, SINT32 LogicFrameID);
VOID   FSP_SetDisplay(SINT32 InstID, SINT32 LogicFrameID, SINT32 IsWaitDisp);
SINT32 FSP_GetDisplay(SINT32 InstID, SINT32 LogicFrameID);
SINT32 FSP_SetStoreType(SINT32 InstID, FSP_PHY_FS_TYPE_E ePhyFsType, SINT32 PhyFsID, FSP_PHY_FS_STORE_TYPE_E eStoreType);
VOID   FSP_RemovePmv(SINT32 InstID, SINT32 LogicFrameID);
IMAGE* FSP_GetFsImagePtr(SINT32 InstID, SINT32 LogicFrameID);
UADDR  FSP_GetPmvAddr(SINT32 InstID, SINT32 LogicFrameID);
SINT32 FSP_IsNewFsAvalible(SINT32 InstID);
VOID   FSP_GetDecFsAddrTab(SINT32 InstID, SINT32 *DecFsNum, SINT32 *DecFsAddrTab, SINT32 *LineNumAddrTab);
VOID   FSP_GetPmvAddrTab(SINT32 InstID, SINT32 *PmvNum, SINT32 *PmvAddrTab);
VOID   FSP_GetInstInfo(SINT32 InstID, FSP_INST_INFO_S *pFspInstInfo);
SINT32 FSP_GetLogicIdByPhyAddr(SINT32 InstID, UADDR PhyAddr);
SINT32 FSP_GetNullLogicFs(SINT32 InstID);
SINT32 FSP_GetFspType(SINT32 InstID);
SINT32 FSP_GetTotalValidFsNum(SINT32 InstID);
SINT32 FSP_ClearContextAll(SINT32 InstID);
SINT32 FSP_GetOccupiedNum(SINT32 Width, SINT32 Height, SINT32 InstID);
SINT32 FSP_IsSpecialFrm(SINT32 InstID, UINT32 PhyAddr);
UINT8  FSP_IsDecFsAvailable(SINT32 InstID, FSP_PHY_FS_RECORD_S *pFs);
UINT8  FSP_IsPmvAvailable(PMV_RECORD_S *pPmv);
SINT32 FSP_SetSingleFrameBuf(SINT32 InstID, FRAME_BUF_S *FrameBuf);
FSP_PHY_FS_S* FSP_GetDecPhyFs(SINT32 InstID, SINT32 LogicFrameID);
FSP_PHY_FS_S* FSP_GetDispPhyFs(SINT32 InstID, SINT32 LogicFrameID);
FSP_LOGIC_FS_S* FSP_GetLogicFs(SINT32 InstID, SINT32 LogicFrameID);
FSP_INST_S* FSP_GetInst(SINT32 InstID);
FSP_PHY_FS_STORE_TYPE_E FSP_GetStoreType(SINT32 InstID, FSP_PHY_FS_TYPE_E ePhyFsType, SINT32 PhyFsID);


#ifdef __cplusplus
}
#endif

#endif

