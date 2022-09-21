/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_plcipher_define.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __DRV_PLCIPHER_DEFINE_H__
#define __DRV_PLCIPHER_DEFINE_H__


#include "linux/mutex.h"

#include "hi_type.h"
#include "hi_module.h"
#include "hi_debug.h"

#define __PLCIPHER_DEBUG_VERSION__ /* when release plcipher SW, mask it */

#ifndef PLCIPHER_TEE_SUPPORT
#define  PLCIPHER_IRQ_NUMBER            (176 + 32)
#define  PLCIPHER_IRQ_NAME              "plcipher_safe"
#else
#define  PLCIPHER_IRQ_NUMBER            (158 + 32)
#define  PLCIPHER_IRQ_NAME              "plcipher"
#endif

#define CI_IV_SIZE                  (16)  /* max 128bit */
#define CI_KEY_SIZE                 (32)  /* max 256bit */

#define PLCIPHER_DESC_TYPE_188 1
#define PLCIPHER_DESC_TYPE_192 4

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pld_nums              : 8   ; /* [7..0]  */
        unsigned int    sid                         : 6   ; /* [13..8]  */
        unsigned int    rsv0                       : 2   ; /* [15..14]  */
        unsigned int    tsid                        : 8   ; /* [23..16]  */
        unsigned int    type                       : 4   ; /* [27..24]  */
        unsigned int    flush                      : 1   ; /* [28]  */
        unsigned int    desep                     : 1   ; /* [29]  */
        unsigned int    rsv1                       : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DESCR_CHAIN_0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    decrypt              : 1   ; /* [0]  */
        unsigned int    chn_secure                         : 1   ; /* [1]  *//*此bit 无效*/
        unsigned int    rsv0                         : 6   ; /* [7..2]  */
        unsigned int    key_id                        : 8   ; /* [15..8]  *//*只有bit0 有效，标示奇偶*/
        unsigned int    rsv1                       : 8   ; /* [23..16]  */
        unsigned int    rsv2                      : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SOC_DEFINE;

typedef struct DESCR_CHAIN
{
   U_DESCR_CHAIN_0  descr0;
   HI_U32           slice_address;
   U_SOC_DEFINE     soc_define;
   HI_U32           user_define_check_code;
}DESCR_CHAIN;


typedef struct
{
    HI_U32  BufPhyAddr;
    HI_U32  BufSmmuAddr;
    HI_U32  BufVirAddr;
    HI_U32  BufLen;
}PLCIPHER_DATA_BUF_S;

#endif		/* __DRV_PLCIPHER_DEFINE_H__ */
