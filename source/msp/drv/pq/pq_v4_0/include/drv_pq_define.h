/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************
File Name   : drv_pq_define.h
Author      : sdk
Version     : v4.0
Abstract    :
*****************************************************************************/

#ifndef _DRV_PQ_DEFINE_V4_H_
#define _DRV_PQ_DEFINE_V4_H_

#include "hi_type.h"

/*****************************************************************************
PQ Software Define
*****************************************************************************/
#define PQ_VERSION      "1.0.2.0"
#define PQ_DEF_NAME     "pqparam"
#define PQ_MAGIC_NUM    "HIPQ"
#if defined(CHIP_TYPE_hi3798cv200)
#define PQ_CHIP_NAME    "3798CV200"
#define PQ_DCI_SUPPORT
#define PQ_HDT_TM_512_SUPPORT
#ifndef HI_PQ_TEE_SUPPORT
#define TNR_NOTEE_SUPPORT
#endif
#elif defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv200_a)
#define PQ_CHIP_NAME    "3798MV200"
#define PQ_ACC_SUPPORT
#define GFXZME_REDUCE_SUPPORT
#define SHARPEN_FHD_SUPPORT
#define PQ_HDT_TM_64_SUPPORT
#ifndef HI_PQ_TEE_SUPPORT
#define TNR_NOTEE_SUPPORT
#endif
#elif defined(CHIP_TYPE_hi3798mv310)
#define PQ_CHIP_NAME    "3798MV310"
#define PQ_ACC_SUPPORT
#define GFXZME_REDUCE_SUPPORT
#define SHARPEN_FHD_SUPPORT
#define PQ_HDT_TM_64_SUPPORT
#ifndef HI_PQ_TEE_SUPPORT
#define TNR_NOTEE_SUPPORT
#endif
#elif defined(CHIP_TYPE_hi3796mv200)
#define PQ_CHIP_NAME    "3796MV200"
#define PQ_ACC_SUPPORT
#define GFXZME_REDUCE_SUPPORT
#define SHARPEN_FHD_SUPPORT
#define PQ_HDT_TM_64_SUPPORT
#ifdef HI_PQ_TEE_SUPPORT
#define TNR_TEE_SUPPORT
#else
#define TNR_NOTEE_SUPPORT
#endif
#endif


/*****************************************************************************
PQ Head File Define
*****************************************************************************/
#define STR_LEN_8                8
#define STR_LEN_32               32
#define STR_LEN_80               80
#define STR_LEN_256              256
#define STR_LEN_1024             1024

#define ACM_Y_NUM                9
#define ACM_S_NUM                13
#define ACM_H_NUM                29

#define PHY_REG_MAX              2560
#define SOFT_REG_MAX             512
#define PQ_ALG_MODULE_MAX        32
#define PQ_HDR_TM_COEF_SIZE      512
#define PQ_HDR_TM_64_COEF_SIZE   64

/*****************************************************************************
PQ Tools Virtual Command
*****************************************************************************/

#define PQ_CMD_VIRTUAL_BIN_EXPORT                                 0xffffff00
#define PQ_CMD_VIRTUAL_BIN_IMPORT                                 0xffffff04
#define PQ_CMD_VIRTUAL_BIN_FIXED                                  0xffffff08
#define PQ_CMD_VIRTUAL_DRIVER_VERSION                             0xffffffff

#define PQ_CMD_VIRTUAL_HD_CTRL                                    0xffff0001
#define PQ_CMD_VIRTUAL_SD_CTRL                                    0xffff0002
#define PQ_CMD_VIRTUAL_DEMO_CTRL                                  0xffff0003
#define PQ_CMD_VIRTUAL_SOURCE_SELECT                              0xffff0004
#define PQ_CMD_VIRTUAL_READ_REGTYPE                               0xffff0005
#define PQ_CMD_VIRTUAL_OUT_MODE                                   0xffff0006

#define PQ_CMD_VIRTUAL_ACM_RECMD_LUT                              0xffff0100
#define PQ_CMD_VIRTUAL_ACM_BLUE_LUT                               0xffff0101
#define PQ_CMD_VIRTUAL_ACM_GREEN_LUT                              0xffff0102
#define PQ_CMD_VIRTUAL_ACM_BG_LUT                                 0xffff0103
#define PQ_CMD_VIRTUAL_ACM_FLESH_LUT                              0xffff0104
#define PQ_CMD_VIRTUAL_ACM_6BCOLOR_LUT                            0xffff0105

#define PQ_CMD_VIRTUAL_DCI_LUT                                    0xffff0200
#define PQ_CMD_VIRTUAL_DCI_BS_LUT                                 0xffff0201

#define PQ_CMD_VIRTUAL_GAMM_PARA                                  0xffff0301
#define PQ_CMD_VIRTUAL_DEGAMM_PARA                                0xffff0302
#define PQ_CMD_VIRTUAL_GFX_GAMM_PARA                              0xffff0303
#define PQ_CMD_VIRTUAL_GFX_DEGAMM_PARA                            0xffff0304

#define PQ_CMD_VIRTUAL_HDR_TM_LUT                                 0xffff0401
#define PQ_CMD_VIRTUAL_HDR_PARA_MODE                              0xffff0402
#define PQ_CMD_VIRTUAL_HDR_TM_XPOS                                0xffff0403
#define PQ_CMD_VIRTUAL_HDR_SRC_LUM                                0xffff0404
#define PQ_CMD_VIRTUAL_HDR_SOFT_PARA                              0xffff0405
#define PQ_CMD_VIRTUAL_HDR_TONE_MAP                               0xffff0406
#define PQ_CMD_VIRTUAL_HDR_SAT_MAP                                0xffff0407
#define PQ_CMD_VIRTUAL_HDR_TM_YMAP                                0xffff0408

#define PQ_CMD_VIRTUAL_ACC_LUT                                    0xffff0500


/*****************************************************************************
PQ Bin Define
*****************************************************************************/

/**
* PQ Param
**/

/*PQ Module����*/
typedef enum hiPQ_ALG_MODULE_E
{
    PQ_ALG_MODULE_DCI = 0,
    PQ_ALG_MODULE_ACM,
    PQ_ALG_MODULE_BUTT,
} PQ_ALG_MODULE_E;

typedef struct hiPQ_FILE_HEADER_S
{
    HI_U32          u32FileCheckSum;             /* �����ļ���У��ͣ�File Header�����˱����⣩��data���������ֽ�У��ͣ����ڼ��������ȷ�Ժ��ж��Ƿ�dirty */
    HI_U32          u32ParamSize;                /* �����ļ���С������File header��data */
    HI_CHAR         u8Version[STR_LEN_32];       /* �汾�ţ��ַ�����ʾ */
    HI_CHAR         u8Author[STR_LEN_32];        /* ����������ǩ�����ַ�����ʾ */
    HI_CHAR         u8Desc[STR_LEN_1024];        /* �汾�������ַ�����ʾ */
    HI_CHAR         u8Time[STR_LEN_32];          /* �����ļ����ɣ���д��ʱ�䣬[0] ~ [5]��yy mm dd hh mm ss��[6]~[7]��������ʱ����PQ���ߴ�PC���Զ���ȡ�������û����� */
    HI_CHAR         u8ChipName[STR_LEN_32];      /* �����ļ�����ʱ��ChipName */
    HI_CHAR         u8SDKVersion[STR_LEN_80];    /* �����ļ�����ʱ��SDK�汾 */
    HI_U32          u32PhyRegNum;                /* �����ļ�����������Ĵ������� */
    HI_U32          u32SoftRegNum;               /* �����ļ���������㷨�������� */
    HI_U32          u32Offset[PQ_ALG_MODULE_MAX];/* �㷨ϵ��ƫ�Ƶ�ַ */
    HI_U32          u32PhyOffset;                /* �㷨�����Ĵ���ƫ�Ƶ�ַ */
} PQ_FILE_HEADER_S;


/**
* DCI Coef
**/

/*DCI�������ñ�*/
typedef struct hiPQ_DCI_LUT_S
{
    HI_S16 s16WgtCoef0[33];
    HI_S16 s16WgtCoef1[33];
    HI_S16 s16WgtCoef2[33];
    HI_U16 u16Gain0;
    HI_U16 u16Gain1;
    HI_U16 u16Gain2;
} PQ_DCI_LUT_S;

/*DCI Black Stretch Lut*/
typedef struct hiPQ_DCI_BSLUT_S
{
    HI_S16 s16BSDelta[320];
} PQ_DCI_BSLUT_S;

typedef struct hiPQ_DCI_COEF_S
{
    PQ_DCI_LUT_S    stPqDciLut;
    PQ_DCI_BSLUT_S  stPqDciBSLut;
} PQ_DCI_COEF_S;


/**
*ACC Coef
**/
#define ACC_LUT_NUM             5
#define ACC_LUT_RESOLUTION      9

typedef struct hi_PQ_ACC_LUT_S
{
    HI_S32 as32AccLut[ACC_LUT_NUM][ACC_LUT_RESOLUTION];
} PQ_ACC_LUT_S;

/**
* ACM Coef
**/

typedef struct hiPQ_ACM_LUT_S
{
    HI_S16 as16Y[ACM_Y_NUM][ACM_S_NUM][ACM_H_NUM];   /**<  */
    HI_S16 as16H[ACM_Y_NUM][ACM_S_NUM][ACM_H_NUM];   /**<  */
    HI_S16 as16S[ACM_Y_NUM][ACM_S_NUM][ACM_H_NUM];   /**<  */
} PQ_ACM_LUT_S;

typedef struct hiPQ_ACM_MODE_S
{
    PQ_ACM_LUT_S stModeRecmd;
    PQ_ACM_LUT_S stModeBlue;
    PQ_ACM_LUT_S stModeGreen;
    PQ_ACM_LUT_S stModeBG;
    PQ_ACM_LUT_S stModeFleshtone;
    PQ_ACM_LUT_S stMode6BColor;
} PQ_ACM_MODE_S;


typedef struct hiPQ_ACM_COEF_S
{
    PQ_ACM_MODE_S stModeLut;
} PQ_ACM_COEF_S;

#if defined(PQ_HDT_TM_512_SUPPORT)
typedef struct hiPQ_HDR_TM_COEF_S
{
    /*ToneMapping*/
    HI_S16 as16TMLut[16][PQ_HDR_TM_COEF_SIZE];
} PQ_HDR_TM_COEF_S;
#elif defined(PQ_HDT_TM_64_SUPPORT)
typedef struct hiPQ_HDR_TM_COEF_S
{
    HI_U32 au32TMLut[PQ_HDR_TM_64_COEF_SIZE];
    HI_U32 au32TM_B100[PQ_HDR_TM_64_COEF_SIZE]; //brightCurve 100
    HI_U32 au32TM_B0[PQ_HDR_TM_64_COEF_SIZE];   //brightCurve 0
    HI_U32 au32TM_D100[PQ_HDR_TM_64_COEF_SIZE]; //darkCurve 100
    HI_U32 au32TM_D0[PQ_HDR_TM_64_COEF_SIZE];   //darkCurve 0
    HI_U32 au32TM_BP[PQ_HDR_TM_64_COEF_SIZE];   //brightProtect
    HI_U32 au32TM_DP[PQ_HDR_TM_64_COEF_SIZE];   //blackProtect
} PQ_HDR_TM_COEF_S;
#endif

/**
* PQ Phy Register
**/

typedef struct hiPQ_PHY_REG_S
{
    HI_U32 u32RegAddr;     //register addr
    HI_U8  u8Lsb;          //register lsb
    HI_U8  u8Msb;          //register msb
    HI_U8  u8SourceMode;   //video source
    HI_U8  u8OutputMode;   //output mode
    HI_U32 u32Module;      //module
    HI_U32 u32Value;       //register value
} PQ_PHY_REG_S;

/**
* PQ_PARAM_S
**/

typedef struct hiPQ_COEF_S
{
#if defined(PQ_DCI_SUPPORT)
    PQ_DCI_COEF_S               stDciCoef;
#endif
#if defined(PQ_ACC_SUPPORT)
    PQ_ACC_LUT_S                stACCCoef;
#endif
    PQ_ACM_COEF_S               stAcmCoef;
    PQ_HDR_TM_COEF_S            stHdrTmCoef;
} PQ_COEF_S;

typedef struct hiPQ_PARAM_S
{
    PQ_FILE_HEADER_S            stPQFileHeader;
    PQ_COEF_S                   stPQCoef;
    PQ_PHY_REG_S                stPQPhyReg[PHY_REG_MAX];
    PQ_PHY_REG_S                stPQSoftReg[SOFT_REG_MAX];
} PQ_PARAM_S;


#endif

