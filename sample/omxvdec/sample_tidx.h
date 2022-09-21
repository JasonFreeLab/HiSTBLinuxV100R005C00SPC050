
#ifndef SAMPLE_TIDX_H
#define SAMPLE_TIDX_H

#define  PACK_OK            (0)
#define  PACK_ERR           (-1)

// 从.tidx文件中读取的帧信息数上限
#define  MAX_LOAD_TIDX_NUM  (30*1024)

/*图像帧信息*/
typedef struct
{
    int   FrameNum;
	int   Frameoffset;
	int   FrameSize;
    int FrameType;              // frame coding type
    int TopFieldType;           // top field coding type
    int BtmFieldType;           // buttom field coding type
    long FramePts;
    int FrameStructure;         // 0-frame ; 1-fieldpair
    int TopFieldCrc;
    int BtmFieldCrc;
    int NVOPFlag;               // NVOP输不输出的标志
    int AlreadyOutPutFlag;      // 帧已经输出标志

}FRAME_INFO_S;

typedef struct
{
    int   TotalFrameNum;
    int   NvopFrameNum;
    int   ErrorCount;
    int   ErrorFrame;
    FILE *fptidxFile;
    FILE *fpPrmFile;
    FILE *fpErrLog;
    FILE *fpErrYuv;
    char *pChromUl;
    char *pChromVl;
    FRAME_INFO_S  stFrameInfotidx[MAX_LOAD_TIDX_NUM];

}STR_CONTEXT_S;

int ReadFrameInfoFromtidx(STR_CONTEXT_S *pstContext);

#endif

