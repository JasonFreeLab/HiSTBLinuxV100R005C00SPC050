/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_sm2_v100.h
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef _DRV_SM2_V1_H_
#define _DRV_SM2_V1_H_

#include "drv_osal_lib.h"

/*! \Define the offset of reg */
#define  SM2_REG_BUSY                   (0x00)
#define  SM2_REG_WORK_MODE              (0x04)
#define  SM2_REG_STRAT                  (0x08)
#define  SM2_REG_DEBUG_EN               (0x10)
#define  SM2_REG_RNG_OPTION             (0x14)
#define  SM2_REG_INT_ENABLE             (0x20)
#define  SM2_REG_INT_STATUS             (0x24)
#define  SM2_REG_NOMASK_STATUS          (0x28)
#define  SM2_REG_RESULT_FLAG            (0x40)
#define  SM2_REG_FAILURE_FLAGS          (0x44)
#define  SM2_REG_RRAM_CTRL_CFG          (0x6c)
#define  SM2_REG_WP_L                   (0x80)
#define  SM2_REG_WP_H                   (0x84)
#define  SM2_REG_OTP_KEY_SEL_EN         (0x88)
#define  SM2_REG_KEY_RANDOM             (0x8c)
#define  SM2_REG_KEY_CRC                (0x90)
#define  SM2_REG_KEY_CFG                (0x9c)
#define  SM2_REG_KEY_RANDOM_A           (0x100)
#define  SM2_REG_MRAM                   (0x200)
#define  SM2_REG_NRAM                   (0x600)
#define  SM2_REG_KRAM                   (0xa00)
#define  SM2_REG_RRAM                   (0xe00)
#define  SM2_RAM_SECTION_SIZE_IN_WORD   (0x18)
#define  SM2_RAM_RANG_SIZE              (0x400)

/*! \Define the operaion mode */
typedef enum
{
    SM2_MODEA_CLR_MRAM = 0x01,
    SM2_MODEA_CLR_KRAM = 0x02,
    SM2_MODEA_CLR_NRAM = 0x04,
    SM2_MODEA_CLR_RRAM = 0x08,
    SM2_MODEA_CLR_PKA  = 0x10,
    SM2_MODEA_CLR_ALLRAM = 0x1F,
    SM2_MODEA_SIZE = 0xFF,
}SM2_MODEA_S;

/*! \Define the ram type */
typedef enum
{
    SM2_RAM_TYPE_MRAM = 0,
    SM2_RAM_TYPE_NRAM,
    SM2_RAM_TYPE_KRAM,
    SM2_RAM_TYPE_RRAM,
}SM2_RAM_TYPE_S;

/*! \Define the operaion code */
typedef enum
{
    SM2_OPCODE_ADD_MOD = 3,
    SM2_OPCODE_SUB_MOD = 5,
    SM2_OPCODE_MUL_MOD = 6,
    SM2_OPCODE_INV_MOD = 7,
    SM2_OPCODE_MOD = 8,
    SM2_OPCODE_MUL = 9,
    SM2_OPCODE_MUL_DOT = 12,
    SM2_OPCODE_ADD_DOT = 13,
    SM2_OPCODE_CLR_RAM = 15,
}SM2_OPCODE_S;

/* Define the union U_SM2_BUSY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sm2_busy              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SM2_BUSY;

/* Define the union U_SM2_WORK_MODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    opcode                : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 4   ; /* [7..4]  */
        unsigned int    mode                  : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SM2_WORK_MODE;

/* Define the union U_SM2_START */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sm2_start             : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SM2_START;

/* Define the union U_SM2_INT_ENABLE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sm2_finish_int_enable : 1   ; /* [0]  */
        unsigned int    sm2_err_int_enable    : 1   ; /* [1]  */
        unsigned int    reserved_0            : 29  ; /* [30..2]  */
        unsigned int    sm2_all_int_enable    : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SM2_INT_ENABLE;

/* Define the union U_SM2_INT_STATUS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    finish_int_status     : 4   ; /* [3..0]  */
        unsigned int    alarm_int_status      : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SM2_INT_STATUS;

/* Define the union U_SM2_INT_NOMASK_STATUS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    finish_int_nomsk_status : 4   ; /* [3..0]  */
        unsigned int    alarm_int_nomsk_status : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SM2_INT_NOMASK_STATUS;

/* Define the union U_SM2_RESULT_FLAG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    SM2_result_flag       : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SM2_RESULT_FLAG;

/* Define the union U_SM2_FAILURE_FLAG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    SM2_failure_flag      : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SM2_FAILURE_FLAG;

#endif /* _DRV_SM2_V1_H_ */
