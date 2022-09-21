/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_trng_v200.h
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef _DRV_TRNG_V200_H_
#define _DRV_TRNG_V200_H_

#include "drv_osal_lib.h"

/*************************** Internal Structure Definition ****************************/
/** \addtogroup      trng drivers*/
/** @{*/  /** <!-- [trng]*/

/*! \Define the offset of reg */
#define  HISEC_COM_TRNG_CTRL            (0x00)
#define  HISEC_COM_TRNG_FIFO_DATA       (0x04)
#define  HISEC_COM_TRNG_DATA_ST         (0x08)

/* Define the union U_HISEC_COM_TRNG_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        u32   osc_sel            :  2;   /* [1..0]  */
        u32   cleardata          :  1;   /* [2]  */
        u32   drbg_enable        :  1;   /* [3]  */
        u32   pre_process_enable :  1;   /* [4]  */
        u32   drop_enable        :  1;   /* [5]  */
        u32   mix_enable         :  1;   /* [6]  */
        u32   post_process_enable:  1;   /* [7]  */
        u32   post_process_depth :  8;   /* [15..8]  */
        u32   reserved0          :  1;   /* [16]  */
        u32   trng_sel           :  2;   /* [18..17]  */
        u32   pos_self_test_en   :  1;   /* [19]  */
        u32   pre_self_test_en     :  1;   /* [20]  */
        u32   reserved1          :  11;  /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    u32    u32;

} U_HISEC_COM_TRNG_CTRL;

/* Define the union U_HISEC_COM_TRNG_DATA_ST */
typedef union
{
    /* Define the struct bits */
    struct
    {
        u32    low_osc_st0        :    1; /* [0]  */
        u32    low_osc_st1        :    1; /* [1]  */
        u32    low_ro_st0         :    1; /* [2]  */
        u32    low_ro_st1         :    1; /* [3]  */
        u32    otp_trng_sel       :    1; /* [4]  */
        u32    reserved0          :    3; /* [7..5]  */
        u32    trng_fifo_data_cnt :    8; /* [15..8]  */
        u32    sic_trng_alarm     :    6; /* [21..16]  */
        u32    sic_trng_bist_alarm:    1; /* [22]  */
        u32    reserved1          :    9; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    u32    u32;

} U_HISEC_COM_TRNG_DATA_ST;

/** @}*/  /** <!-- ==== Structure Definition end ====*/
#endif
