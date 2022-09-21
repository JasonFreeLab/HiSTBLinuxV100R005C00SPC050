//?????????????,???????,????,????,??????
//
//
#ifndef __VPSS_CBB_COMMON_H__
#define __VPSS_CBB_COMMON_H__

//#include <stdio.h>
//#include <string.h>
#include "hi_type.h"
#include "hi_reg_common.h"
#include "vpss_cbb_reg.h"
//#include "vpss_stt_reg.h"
//#include "vpss_basefunc.h"
#include "vpss_cbb_hal.h"
#include "vpss_cbb_hal_mmu.h"
#include "vpss_cbb_hal_sys.h"
#include "vpss_cbb_hal_tnr.h"
#include "vpss_cbb_hal_snr.h"
#include "vpss_cbb_hal_mac.h"
#include "vpss_cbb_hal_die.h"
#include "vpss_cbb_hal_zme.h"
#include "vpss_cbb_hal_vc1.h"
#include "vpss_cbb_hal_crop.h"
#include "vpss_cbb_hal_lba.h"

#define DEF_CBB_MAX_NODE_NUM VPSS_HAL_NODE_BUTT

#define VPSS_MULTI_VER 4096
#define VPSS_MULTI_HOR 1048576

//#define VPSS_RegRead(addr) printk("R ADDR:0x%x VAL:%u\n", (unsigned int)(addr), *(volatile unsigned int *)(addr))
//#define VPSS_RegWrite(addr, value) //printk("W ADDR:0x%x VAL:%u\n", (unsigned int)(addr), (value));

//#define VPSS_REG_RegWrite VPSS_RegWrite
//#define VPSS_REG_RegRead VPSS_RegRead

//#define printf

typedef struct
{
    HI_U32 u32BasePhyAddr;   //???????
    HI_U8 *pu8BaseVirAddr;   //???????

    HI_U32 u32NodePhyAddr;   //DDR????????
    HI_U8 *pu8NodeVirAddr;   //DDR????????
} CBB_REG_ADDR_S;

typedef enum
{
    CBB_BITWIDTH_8BIT = 0,
    CBB_BITWIDTH_10BIT,
    CBB_BITWIDTH_12BIT,
    CBB_BITWIDTH_10BIT_CTS,
    CBB_BITWIDTH_BUTT,
} CBB_BITWIDTH_E;

typedef struct
{
    HI_U32 u32PhyAddr_YHead;
    HI_U32 u32PhyAddr_Y;
    HI_U8 *pu8VirAddr_YHead;
    HI_U8 *pu8VirAddr_Y;
    HI_BOOL bSmmu_Y;
    HI_BOOL bSmmu_YHead;

    HI_U32 u32PhyAddr_CHead;
    HI_U32 u32PhyAddr_C;
    HI_U8 *pu8VirAddr_CHead;
    HI_U8 *pu8VirAddr_C;
    HI_BOOL bSmmu_C;
    HI_BOOL bSmmu_CHead;

    HI_U32 u32Stride_Y;
    HI_U32 u32Stride_C;

    HI_U32  u32Head_Stride;
    HI_U32  u32Head_Size;
} CBB_FRAME_ADDR_S;

typedef enum
{
    INPUTFMT_LINEAR_SP420            = 0x0,
    INPUTFMT_SEMIPLANAR_422_2X1      = 0x1,
    INPUTFMT_TILE_SP420              = 0x2,
    INPUTFMT_400                     = 0x3,
    INPUTFMT_TILE_400                = 0x4,
    INPUTFMT_PLANAR_444              = 0x5,
    INPUTFMT_PLANAR_422_2X1          = 0x6,
    INPUTFMT_PLANAR_422_1X2          = 0x7,
    INPUTFMT_PLANAR_420              = 0x8,
    INPUTFMT_PLANAR_411              = 0x9,
    INPUTFMT_PLANAR_410              = 0xa,
    INPUTFMT_PACKAGE_422_YUYV        = 0xb,
    INPUTFMT_PACKAGE_422_YVYU        = 0xc,
    INPUTFMT_PACKAGE_422_UYVY        = 0xd,

    INPUTFMT_LINEAR_SP444            = 0x15,
    INPUTFMT_BUTT
} CBB_PIXEL_FMT_E;


typedef struct
{
    HI_U32 u32NodePhyAddr[DEF_CBB_MAX_NODE_NUM];
    HI_U8 *pu8NodeVirAddr[DEF_CBB_MAX_NODE_NUM];
    HI_U32 u32NodeValid[DEF_CBB_MAX_NODE_NUM];
} CBB_START_CFG_S;

#if 0
typedef struct
{
    HI_U32 u32X;
    HI_U32 u32Y;
    HI_U32 u32Wth;
    HI_U32 u32Hgt;
} HI_RECT_S;
#endif

typedef struct
{
    HI_U32 u32ROutStd;
    HI_U32 u32WOutStd;
} CBB_OUTSTANDING_S;


typedef enum
{
    AXI_BURST_LEN_16 = 0x0,
    AXI_BURST_LEN_8,
    AXI_BURST_LEN_4,
} CBB_AXI_BURST_LEN_E;

typedef struct
{
    HI_U32 u32BurstLen;
    HI_U32 u32Split128;
    HI_U32 u32Split256;
} CBB_BUS_CTRL_S;

typedef struct
{
    CBB_BUS_CTRL_S      stBusCtrl;
    CBB_OUTSTANDING_S   stOutStanding;
} CBB_AXI_CFG_S;

typedef enum
{
    /* vhd0?????????:
        0:????2?;
        1:????4?;
        2:????8?;
        3:????
    */
    CBB_FIR_X2 = 0,
    CBB_FIR_X4 = 1,
    CBB_FIR_X8 = 2,
    CBB_FIR_EXT_BOTTOM = 3, //extract bottom field
    CBB_FIR_BUTT,
} CBB_FIR_MODE_E;

typedef enum
{
    CBB_TUNOUT_2 = 0,
    CBB_TUNOUT_4 = 1,
    CBB_TUNOUT_8 = 2,
    CBB_TUNOUT_16 = 3,
    CBB_TUNOUT_BUTT,
} CBB_TUNOUT_MODE_E;


typedef enum
{
    CBB_COLOR_BLACK = 0,
    CBB_COLOR_RED,
    CBB_COLOR_WHITE,
    CBB_COLOR_GREEN,
    CBB_COLOR_BLUE,
    CBB_COLOR_YELLOW,
    CBB_COLOR_BUTT,
} CBB_COLOR_E;

typedef enum
{
    CBB_FREAM_BUF_8BIT = 0,
    CBB_FREAM_BUF_2BIT_LB,
    CBB_FREAM_BUF_CMP_HEADER,
    CBB_FREAM_BUF_BUTT,
    CBB_FREAM_BUF_CNT = CBB_FREAM_BUF_BUTT,
} CBB_FRAME_BUF_TYPE_E;


typedef enum
{
    CBB_ZME_MODE_HOR = 0 ,
    CBB_ZME_MODE_VER     ,

    CBB_ZME_MODE_HORL    ,
    CBB_ZME_MODE_HORC    ,
    CBB_ZME_MODE_VERL    ,
    CBB_ZME_MODE_VERC    ,

    CBB_ZME_MODE_ALL     ,
    CBB_ZME_MODE_NONL    ,

    CBB_ZME_MODE_BUTT
} CBB_ZME_MODE_E;

typedef enum
{
    CBB_RAM_MODE_SDI     = 0,
    CBB_RAM_MODE_HDI     = 1,
    CBB_RAM_MODE_SDP     = 2,
    CBB_RAM_MODE_HDP     = 3,
    CBB_RAM_MODE_RTT     = 4,
    CBB_RAM_MODE_BYPASS  = 5,
    CBB_RAM_MODE_10bit   = 6,
    CBB_RAM_MODE_BUTT,
} CBB_RAM_MODE_E;

#endif
