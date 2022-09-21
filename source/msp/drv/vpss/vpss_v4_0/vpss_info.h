
#ifndef __VPSS_DEBUG_H__
#define __VPSS_DEBUG_H__
#include "vpss_common.h"
#include "hi_drv_vpss.h"
#include "vpss_osal.h"

#define VPSS_CODE_TIMESTAMP     "2017-7-7 14:04:35"
#define VPSS_CODE_VERSION       "2017-7-7"
#define VPSS_CODE_LASTGITNO     "710820bacbda43991d1c9c74086c14c80474499f"
#ifdef HI_NVR_SUPPORT
#define VPSS_CODE_MODE          "NVR"
#else
#define VPSS_CODE_MODE          "Normal"
#endif

#define DEF_DBG_CMD_YUV         "saveyuv"
#define DEF_DBG_CMD_YUVIDX      "saveyuvidx"
#define DEF_DBG_CMD_YUVFILE     "saveyuvfile"
#define DEF_DBG_CMD_REVISEIMGWH "setsrcwh"
#define DEF_DBG_CMD_LBOXCOLOR   "setcolor"
#define DEF_DBG_CMD_STREAM      "savestream"
#define DEF_DBG_CMD_FRAME_INFO  "printinfo"
#define DEF_DBG_CMD_NONE   "none"
#define DEF_DBG_CMD_UHD_HIGH "high"
#define DEF_DBG_CMD_UHD_MIDDLE "middle"
#define DEF_DBG_CMD_UHD_LOW "low"
#define DEF_DBG_CMD_UHD_USR "adaptive"
#define DEF_DBG_CMD_SET_UV  "uvinvert"
#define DEF_DBG_CMD_CMP_ON     "cmpon"
#define DEF_DBG_CMD_CMP_OFF    "cmpoff"
#define DEF_DBG_CMD_SET_I2P "i2p"
#define DEF_DBG_CMD_SETBYPASS  "setbypass"
#define DEF_DBG_CMD_SETRATE    "setrate"
#define DEF_DBG_CMD_SETOUTBITWIDTH "setbitwidth"
#define DEF_DBG_CMD_SETROTATION "setrota"
#define DEF_DBG_CMD_SETPROCLEVEL "proc"
#define DEF_DBG_CMD_RESET  "reset"

#define DEF_DBG_SRC    "src"
#define DEF_DBG_PORT_0 "port0"
#define DEF_DBG_PORT_1 "port1"
#define DEF_DBG_PORT_2 "port2"

#define DEF_DBG_SET_ON "on"
#define DEF_DBG_SET_OFF "off"

#define DEF_DBG_SET_OUTWIDTH_8BIT "8bit"
#define DEF_DBG_SET_OUTWIDTH_10BIT "10bit"
#define DEF_DBG_SET_OUTWIDTH_12BIT "12bit"

#define DEF_DBG_ROTATION_0          "0"
#define DEF_DBG_ROTATION_90         "90"
#define DEF_DBG_ROTATION_180        "180"
#define DEF_DBG_ROTATION_270        "270"

#define DEF_DBG_COLOR_RED           "red"
#define DEF_DBG_COLOR_BLUE          "blue"
#define DEF_DBG_COLOR_GREEN         "green"
#define DEF_DBG_COLOR_WHITE         "white"
#define DEF_DBG_COLOR_BLACK         "black"
#define DEF_DBG_COLOR_YELLOW        "yellow"

#define DEF_DBG_PROCLEVEL_ORI       "0"
#define DEF_DBG_PROCLEVEL_1         "1"
#define DEF_DBG_PROCLEVEL_2         "2"
#define DEF_DBG_PROCLEVEL_3         "3"
#define DEF_DBG_SRC_ID    0x0
#define DEF_DBG_PORT0_ID  0x1
#define DEF_DBG_PORT1_ID  0x2
#define DEF_DBG_PORT2_ID  0x3
#define DEF_DBG_SRC_PORT_BUT 0xFFFFFFFF

#define VPSS_PROC_MSG_PRINT HI_PRINT
#define VPSS_PROC_INFO_PRINT PROC_PRINT

typedef enum hiVPSS_DEBUG_E
{
    DBG_W_YUV = 0,
    DBG_W_STREAM ,
    DBG_INFO_FRM ,
    DBG_INFO_NONE ,
    DBG_INFO_ASP,
    DBG_SET_UHD,
    DBG_SET_UHD_LOW,
    DBG_SET_UHD_MID,
    DBG_SET_UHD_HIGH,
    DBG_SET_UHD_USR,
    DBG_SET_UV_INVERT,
    DBG_SET_CMP_ON,
    DBG_SET_CMP_OFF,
    DBG_SET_I2P,
    DBG_SET_FRMRATE,
    DBG_SET_RATATION,
    DBG_SET_OUTBITWIDTH,
    DBG_W_YUV_IDX,
    DBG_W_YUV_FILE,
    DBG_REVISE_SRC_WH,
    DBG_SET_LBX_COLOR,
    DBG_BUTT
} VPSS_DEBUG_E;
typedef enum hiVPSS_PROC_PRINT_LEVEL_E
{
    PROC_PRINT_LEVEL_ORI = 0x0,
    PROC_PRINT_LEVEL1,
    PROC_PRINT_LEVEL2,
    PROC_PRINT_LEVEL3,
    PROC_PRINT_BUTT
} VPSS_PROC_PRINT_LEVEL_E;

typedef struct hiVPSS_DBG_YUV_S
{
    VPSS_HANDLE hPort;
    HI_CHAR chFile[DEF_FILE_NAMELENGTH];
} VPSS_DBG_YUV_S;

typedef union
{
    VPSS_HANDLE hYuvPart;
    VPSS_HANDLE hDbgPart;
} DBG_CMD_PARA_U;

typedef struct hiVPSS_DBGCMD_S
{
    VPSS_DEBUG_E enDbgType;

    VPSS_HANDLE hDbgPart;
    VPSS_HANDLE hDbgValue;
    //DBG_CMD_PARA_U unPara;
} VPSS_DBG_CMD_S;

typedef union
{
    // Define the struct bits
    struct
    {
        unsigned int    imginfo              : 1   ;
        unsigned int    dei                  : 1   ;
        unsigned int    writeyuv             : 4   ;
        unsigned int    writestream          : 1   ;
        unsigned int    writestreamIdx       : 1   ;
        unsigned int    vpssbypass           : 1   ;
        unsigned int    frameEn              : 1   ;
        unsigned int    framerate            : 8   ;

        unsigned int    start_index          : 16  ;
        unsigned int    end_index            : 16  ;

        unsigned int    reserve_2            : 14  ;
    } bits;
    // Define an unsigned member
    unsigned long long    u64;
} DBG_INST_INFO_U;
typedef union
{
    // Define the struct bits
    struct
    {
        unsigned int    frameinfo            : 1   ;
        unsigned int    asp                  : 1   ;
        unsigned int    writeyuv             : 4   ;
        unsigned int    writestream          : 1   ;
        unsigned int    writestreamIdx       : 1   ;
        unsigned int    uv_invert            : 1   ;
        unsigned int    cmp                  : 2   ;  //defalt 0, ON 01, OFF 02, 03 reserved

        unsigned int    dbg_rotation_en      : 1  ;
        unsigned int    dbg_rotation_angle   : 2  ;

        unsigned int    dbg_output_bitwidth_en  : 1  ;
        unsigned int    output_bitwidth_mode : 2  ;

        unsigned int    start_index          : 16  ;
        unsigned int    end_index            : 16  ;
        unsigned int    dbg_lbox_color_en    : 1  ;
        unsigned int    dbg_lbox_color_mode  : 3  ;

        unsigned int    reserve_2            : 11  ;
    } bits;
    // Define an unsigned member
    unsigned long long    u64;
} DBG_PORT_INFO_U;

typedef struct hiVPSS_DBG_PORT_S
{
    DBG_PORT_INFO_U unInfo;
    HI_U32 u32LastH;
    HI_U32 u32LastM;
    HI_U32 u32LastS;
} VPSS_DBG_PORT_S;

typedef struct hiVPSS_DBG_INST_S
{
    DBG_INST_INFO_U unInfo;
    HI_U32 u32LastH;
    HI_U32 u32LastM;
    HI_U32 u32LastS;
    HI_U32 u32UhdSetW;
    HI_U32 u32UhdSetH;

    HI_BOOL bReviseSrcWH;
    HI_BOOL bResetPerFrame;
    HI_U32 u32SrcWH;
#ifdef VPSS_SUPPORT_PROC_V2
    VPSS_PROC_PRINT_LEVEL_E eProcPrintLevel;
#endif
} VPSS_DBG_INST_S;

typedef struct hiVPSS_DBG_S
{
    VPSS_DBG_INST_S stInstDbg;

    VPSS_DBG_PORT_S stPortDbg[DEF_HI_DRV_VPSS_PORT_MAX_NUMBER];
} VPSS_DBG_S;

HI_S32 VPSS_DBG_DbgInit(VPSS_DBG_S *pstDbg);

HI_S32 VPSS_DBG_DbgDeInit(VPSS_DBG_S *pstDbg);

HI_S32 VPSS_DBG_SendDbgCmd(VPSS_DBG_S *pstDbg, VPSS_DBG_CMD_S *pstCmd);

HI_S32 VPSS_DBG_ReplyDbgCmd(VPSS_DBG_S *pstDbg, VPSS_DEBUG_E enCmd, HI_VOID *para1, HI_VOID *para2);

HI_VOID VPSS_DBG_PrintFrameInfo(HI_DRV_VIDEO_FRAME_S *pstFrame, HI_BOOL bSrcFrame, HI_U32 u32StartIndex, HI_U32 u32EndIndex);
#endif
