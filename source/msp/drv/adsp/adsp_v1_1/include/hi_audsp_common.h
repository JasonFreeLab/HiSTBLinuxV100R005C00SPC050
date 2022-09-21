/*--------------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_audsp_common.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2012/10/08
  Description   :
  History       :
  1.Date        : 2013/02/28
    Author      : zgjie
    Modification: Created file

 *******************************************************************************/

#ifndef __HI_AUDSP_COMMON__H__
#define __HI_AUDSP_COMMON__H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if defined (__XTENSA__)
/* only use these in dsp firmware */

#define typeof __typeof__

/**
 * offsetof(type, member)
 *
 * @type: The type of the structure
 * @member: The member within the structure to get the offset of
 */
#define offsetof(type, member) ((unsigned int)&((type *)0)->member)

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:    the pointer to the member.
 * @type:   the type of the container struct this is embedded in.
 * @member: the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({          \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})

#endif

/*************** HIFI DSP subsystem SOC Definition ******************/

#if    defined(CHIP_TYPE_hi3751v100)   \
    || defined(CHIP_TYPE_hi3751v100b)  \
    || defined(CHIP_TYPE_hi3751v600)   \
    || defined(CHIP_TYPE_hi3751lv500)  \
    || defined(CHIP_TYPE_hi3751v500)   \
    || defined(CHIP_TYPE_hi3751v620)

#ifndef HI_FPGA
//ASIC
#define DSP0_CLOCK_HZ     (300 * 1000 * 1000)    /*300M asic*/
#else
//FPGA
#define DSP0_CLOCK_HZ     (50 * 1000 * 1000)     /*50M fpga*/
#endif

#elif  defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)   \
    || defined(CHIP_TYPE_hi3716dv100)   \
    || defined(CHIP_TYPE_hi3798cv200)   \
    || defined(CHIP_TYPE_hi3716mv420)   \
    || defined(CHIP_TYPE_hi3716mv410)   \
    || defined(CHIP_TYPE_hi3798mv200)   \
    || defined(CHIP_TYPE_hi3798mv300)	\
    || defined(CHIP_TYPE_hi3798mv200_a) \
    || defined(CHIP_TYPE_hi3796mv200)
#ifdef HI_FPGA
#define DSP0_CLOCK_HZ     (30 * 1000 * 1000)    /*30M FPGA*/
#else
#define DSP0_CLOCK_HZ     (500 * 1000 * 1000)    /*500M asic*/
#endif
#else
#error YOU MUST DEFINE  CHIP_TYPE!
#endif

#ifdef HI_FPGA
#define DSP_ACK_TIME 500
#else
#define DSP_ACK_TIME 100
#endif

#define DSP0_TIMER0_INTERVAL (DSP0_CLOCK_HZ/200)           /* 5  ms */
#define DSP0_TIMER1_INTERVAL (DSP0_CLOCK_HZ/200)           /* 5  ms */
#define DSP0_TIMER0_INTERVAL_CAST (DSP0_CLOCK_HZ/200)      /* 5  ms */
#define DSP0_TIMER1_INTERVAL_CAST (DSP0_CLOCK_HZ/200)      /* 5  ms */

/* arm interrupt Definition */
#define ADSP0TOA9_IRQ_NUM (51)

/* dsp interrupt Definition */
#define DSP_INTERRUPT_DSP2DSP                0x0
#define DSP_INTERRUPT_A9TODSP                0x1
#define DSP_INTERRUPT_MCE2DSP                0x2
#define DSP_INTERRUPT_M3TODSP                0x3
#define DSP_INTERRUPT_WDG                    0x4
#define DSP_INTERRUPT_SWIOPERI               0x5
#define DSP_INTERRUPT_TIMER0                 0x6
#define DSP_INTERRUPT_SOFTINT1               0x7
#define DSP_INTERRUPT_SWI1PERI               0x8
#define DSP_INTERRUPT_SWI2PERI               0x9
#define DSP_INTERRUPT_TIMER1                 0xa
#define DSP_INTERRUPT_SOFTINT2               0xb
#define DSP_INTERRUPT_RESERVE0               0xc
#define DSP_INTERRUPT_TIMER2                 0xd
#define DSP_INTERRUPT_NMI                    0xe
#define DSP_INTERRUPT_AIAO2DSP               0xf
#define TIMER0_INT_MASK (1 << DSP_INTERRUPT_TIMER0)
#define TIMER1_INT_MASK (1 << DSP_INTERRUPT_TIMER1)

/* DSP on-chip Sram memory Addr Definition */

#ifdef HI_SND_DSP_SUPPORT
#define DSP0_SHARESRAM_BASEADDR    0xf9868000  // 96mv200 TCM addr
#else
#define DSP0_SHARESRAM_BASEADDR    0xffff5000
#endif

#define DSP0_SHARESRAM_MAXSIZE     0x01000
#define DSP0_SHARESRAM_AOE_OFFSET  0x0000
#define DSP0_SHARESRAM_AFLT_OFFSET 0x0b00
#define DSP0_SHARESRAM_SYS_OFFSET  0x0f00
#define DSP0_SHARESRAM_SYS_SIZE    0x0040
#define DSP0_SHARESRAM_CHAN0_BASEADDR     (DSP0_SHARESRAM_BASEADDR+DSP0_SHARESRAM_SYS_OFFSET)
#define DSP0_SHARESRAM_CHAN1_BASEADDR     (DSP0_SHARESRAM_BASEADDR+DSP0_SHARESRAM_SYS_OFFSET+DSP0_SHARESRAM_SYS_SIZE)

#define DSP0_SHARESRAM_RESERVESIZE     (0x00100)
#define DSP0_SHARESRAM_ALIGN (128)

/* DSP running code&data DDR memory Addr  Definition */
//#define DSP_DDR_CODE_BASEADDR 0x3800000    /* 32M - 40M */
#define DSP_DDR_CODE_BASEADDR 0x7800000    /* 120M - 128M */
#define DSP_DDR_CODE_MAXSIZE  0x0800000

#define DSP_DDR_CACHE_DMA_SUPPORT   /* default */
//#define DSP_DDR_DMAREMAP_SUPPORT
#if defined (DSP_DDR_CACHE_DMA_SUPPORT)
/* DSP DMA buffer is cacheable, dsp invalidate dcache before read dma & dsp writeback dcache after write dma */
#undef DSP_DDR_DMAREMAP_SUPPORT
#elif defined (DSP_DDR_DMAREMAP_SUPPORT)
/* DSP DMA buffer is uncacheable, remap DMA ddr memory to DSP_DDR_DMAREMAP_MAP_ADDR avoid conflict with
dsp running(code&data) memory DSP_DDR_DMAREMAP_BEG_ADDR~DSP_DDR_DMAREMAP_END_ADDR */
#undef DSP_DDR_CACHE_DMA_SUPPORT
#else
/* DSP DMA buffer & running(code&data) memory is uncache */
#undef DSP_DDR_CACHE_DMA_SUPPORT
#undef DSP_DDR_DMAREMAP_SUPPORT
#endif

#define DSP_DDR_DMAREMAP_BEG_ADDR  0x00000000    /* 512M,(0x00000000~0x1fffffff) */
#define DSP_DDR_DMAREMAP_END_ADDR  0x20000000    /* 512M, 0x20000000 */
#define DSP_DDR_DMAREMAP_MAP_ADDR  0xc0000000    /* 6*512M，must sure dsp never use this phy addr(0xc0000000~0xdfffffff) */

#define DSP_DEBUG_REG_NUM 4
#define DSP_PRIVDEBUG_REG_NUM 4

/* Define the union U_ADSP_ATTR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dis_lowpower          : 1   ; /* [0]  */
        unsigned int    Reserved_2            : 3   ; /* [3..1]  */
        unsigned int    fsm                   : 4   ; /* [7..4]  */
        unsigned int    Reserved_1            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ADSP_ATTR;

/* Define the union U_ADSP_ATTR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    aoe_percent           : 8   ; /* [7..0]  */
        unsigned int    aflt_percent          : 8   ; /* [15..8]  */
        unsigned int    idle_percent          : 8  ;  /* [23..16]  */
        unsigned int    Reserved              : 8   ; /* [31..24]  */

    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ADSP_STATISTICS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sys_cmd               : 2   ; /* [1..0]  */
        unsigned int    Reserved_0            : 1   ; /* [2]  */
        unsigned int    sys_cmd_done          : 1   ; /* [3]  */
        unsigned int    sys_cmd_return_value  : 4   ; /* [7..4]  */

        unsigned int    aoe_cmd               : 2   ; /* [9..8]  */
        unsigned int    Reserved_1            : 1   ; /* [10]  */
        unsigned int    aoe_cmd_done          : 1   ; /* [11]  */
        unsigned int    aoe_cmd_return_value  : 4   ; /* [15..12]  */

        unsigned int    aflt_cmd               : 2   ; /* [17..16]  */
        unsigned int    Reserved_2            : 1   ; /* [18]  */
        unsigned int    aflt_cmd_done          : 1   ; /* [19]  */
        unsigned int    aflt_cmd_return_value  : 4   ; /* [23..20]  */

        unsigned int    Reserved_3            : 8   ; /* [31..24]  */

    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ADSP_CTRL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    day               : 8   ; /* [7..0]  */
        unsigned int    month             : 8   ; /* [15..8]  */
        unsigned int    year              : 8   ; /* [23..16]  */
        unsigned int    Reserved          : 8  ; /* [31..24]  */

    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ADSP_DATE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    second           : 8   ; /* [7..0]  */
        unsigned int    minute           : 8   ; /* [15..8]  */
        unsigned int    hour             : 8   ; /* [23..16]  */
        unsigned int    Reserved         : 8   ; /* [31..24]  */

    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ADSP_TIME;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_ADSP_ATTR          ADSP_ATTR;
    volatile U_ADSP_STATISTICS    ADSP_STATISTICS;
    volatile U_ADSP_CTRL          ADSP_SYSCTRL;
    volatile unsigned int         ADSP_TIMER1_CNT;
    volatile unsigned int         ADSP_TIMER0_CNT;   /* reserved */
    volatile U_ADSP_DATE          ADSP_DATE;
    volatile U_ADSP_TIME          ADSP_TIME;
    volatile unsigned int         ADSP_DEBUG[DSP_DEBUG_REG_NUM];
    volatile unsigned int         ADSP_PRIVDEBUG[DSP_PRIVDEBUG_REG_NUM];
    volatile unsigned int         ADSP_RESERVED[5-DSP_PRIVDEBUG_REG_NUM];

} S_ADSP_CHN_REGS_TYPE;

/** Audio DSP Code definition*/
/** CNcomment:音频处理器模块代码标识定义 */
typedef enum hiADSP_CODEID_E
{
    /* dsp manage module */
    ADSP_CODE_SYSTEM = 0x0000,  /* dsp system  */
    ADSP_CODE_AOE,   /* audio output engine  */
    ADSP_CODE_AFLT,  /* audio aflt engine  */

    /* dsp decoder module */
    ADSP_CODE_DEC_MP2 = 0x0100,   /* MPEG audio layer 1, 2 */
    ADSP_CODE_DEC_MP3,            /* MPEG audio layer 1, 2 or 3 */
    ADSP_CODE_DEC_AAC,
    ADSP_CODE_DEC_DDP,
    ADSP_CODE_DEC_DTS,
    ADSP_CODE_DEC_TRUEHD,
    ADSP_CODE_DEC_WMASTD,
    ADSP_CODE_DEC_WMAPRO,
    ADSP_CODE_DEC_DRA,

    /* dsp encoder module */
    ADSP_CODE_ENC_AAC = 0x200,

    /* dsp codec module */
    ADSP_CODE_CODEC_AMRNB = 0x400,
    ADSP_CODE_CODEC_AMRWB,

    /* dsp SRS advance effect */
    ADSP_CODE_ADV_SRS_STUDIOSOUND_3D = 0x800,
    ADSP_CODE_ADV_SRS_STUDIOSOUND_HD = 0x800,

    /* dsp Dolby advance effect */
    ADSP_CODE_ADV_DOLBYDV258 = 0x810,
} ADSP_CODEID_E;

typedef struct
{
    HI_BOOL bAoeSwFlag;
    HI_VOID* pAoeRegVirAddr;
    HI_PHYS_ADDR_T tAoeRegPhyAddr;
} AOE_FW_INFO_S;

typedef enum
{
    ADSP_MEMCPY_DSP2DSP = 0x0,
    ADSP_MEMCPY_DSP2ARM,
    ADSP_MEMCPY_ARM2DSP,
    ADSP_MEMCPY_ARM2ARM
} ADSP_MEMCPY_DIR_E;

typedef struct
{
    volatile unsigned int         ADDR_LOW;
    volatile unsigned int         ADDR_HIGH;
} S_AOE_ADDR_TYPE;

/*
 * 作用: ADSP_WriteAddr将地址写入寄存器，ADSP_ReadAddr从寄存器中取出地址
 * addr支持类型: 1、HI_VOID* 2、32位物理地址 3、内核虚拟地址(32位系统中为32bit，64位系统中为64bit)
 * reg必须为S_AOE_ADDR_TYPE结构体类型
 */
/* 使用中间变量传递64位虚拟地址，避免出现强制使用时的对齐问题 */
#define ADSP_WriteAddr(addr, reg) \
    do { \
        S_AOE_ADDR_TYPE reg_tmp = {0x0, 0x0}; \
        *((typeof(addr)*)(&reg_tmp)) = addr; \
        reg.ADDR_LOW = reg_tmp.ADDR_LOW; \
        reg.ADDR_HIGH = reg_tmp.ADDR_HIGH; \
    } while (0)

#define ADSP_ReadAddr(reg, addr) \
    do { \
        S_AOE_ADDR_TYPE reg_tmp = {0x0, 0x0}; \
        reg_tmp.ADDR_LOW = reg.ADDR_LOW; \
        reg_tmp.ADDR_HIGH = reg.ADDR_HIGH; \
        addr = *((typeof(addr)*)(&reg_tmp)); \
    } while (0)

//==============================================================================
/* Define the union U_AIAO_INT_SWI_CPU2DSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi_cpu2dsp       : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_AIAO_INT_SWI_CPU2DSP;

/* Define the union U_AIAO_INT_SWI_DSP2CPU */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi_dsp2cpu       : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_AIAO_INT_SWI_DSP2CPU;

/* Define the union U_AIAO_INT_SWI0_DSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi0_dsp          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_AIAO_INT_SWI0_DSP;

/* Define the union U_AIAO_INT_SWI1_DSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi1_dsp          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_AIAO_INT_SWI1_DSP;

/* Define the union U_AIAO_INT_SWI2_DSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi2_dsp          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_AIAO_INT_SWI2_DSP;

/* Define the union U_AIAO_DSP_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    runstall_dsp0         : 1   ; /* [8]  */
        unsigned int    statvectorsel_dsp0    : 1   ; /* [9]  */
        unsigned int    ocdhaltonreset_dsp0   : 1   ; /* [10]  */
        unsigned int    reserved_1            : 1   ; /* [11]  */
        unsigned int    wdg1_en_dsp0          : 1   ; /* [12]  */
        unsigned int    syn_dbg_sel_dsp0      : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_AIAO_DSP_CTRL;

/* Define the union U_AIAO_DSP_STATUS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    peri_pwaitmode_dsp0   : 1   ; /* [2]  */
        unsigned int    peri_xocdmode_dsp0    : 1   ; /* [3]  */
        unsigned int    reserved_1            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_AIAO_DSP_STATUS;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           AIAO_DSP_START_00; //0xf8cdf000
    volatile unsigned int           AIAO_DSP_START_01;
    volatile unsigned int           AIAO_DSP_START_02;
    volatile unsigned int           AIAO_DSP_START_03;
    volatile unsigned int           AIAO_DSP_START_04; //0xf8cdf010
    volatile unsigned int           AIAO_DSP_START_05;
    volatile unsigned int           AIAO_DSP_START_06;
    volatile unsigned int           AIAO_DSP_START_07;
    volatile U_AIAO_INT_SWI_CPU2DSP AIAO_INT_SWI_CPU2DSP; //0xf8cdf020
    volatile U_AIAO_INT_SWI_DSP2CPU AIAO_INT_SWI_DSP2CPU;
    volatile U_AIAO_INT_SWI0_DSP    AIAO_INT_SWI0_DSP;
    volatile unsigned int           Reserved;             //0xf8cdf02c
    volatile U_AIAO_INT_SWI1_DSP    AIAO_INT_SWI1_DSP;    //0xf8cdf020
    volatile U_AIAO_INT_SWI2_DSP    AIAO_INT_SWI2_DSP;
    volatile U_AIAO_DSP_CTRL        AIAO_DSP_CTRL;
    volatile U_AIAO_DSP_STATUS      AIAO_DSP_STATUS;
} S_AIAO_DSP_REGS_TYPE;

#define DSP0_CTRL_REG_ADDR    0xf8cdf000

/* Define the union HI_DRV_ADSP_SYS_REG_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dsp_ready             : 1   ; /* [0]  */
        unsigned int    arm_ready             : 1   ; /* [1]  */
        unsigned int    test                  : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} HI_DRV_ADSP_STATUS_REG_S;

//==============================================================================

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
