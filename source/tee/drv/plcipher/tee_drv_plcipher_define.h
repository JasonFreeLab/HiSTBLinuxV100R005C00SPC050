/******************************************************************************

  Copyright (C), 2011-2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : tee_drv_plcipher_define.h
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


#include "hi_type.h"

#include "linux_bitmaps.h"
#include "hi_tee_plcipher.h"
#include "tee_plcipher_utils.h"
#include "tee_drv_plcipher_config.h"
#include "tee_drv_plcipher_reg.h"
#include "tee_drv_common.h"

#define __PLCIPHER_DEBUG_VERSION__ /* when release plcipher SW, mask it */

#define TEE_PLCIPHER_MEMCPY asm_memmove

#define PLCIPHER_INVALID_CHN        (0xffffffff)

#define CI_IV_SIZE                  (16)  /* max 128bit */
#define CI_KEY_SIZE                 (32)  /* max 256bit */

#define PLCIPHER_DESC_TYPE_188 1
#define PLCIPHER_DESC_TYPE_192 4

typedef struct hiPLCIPHER_DESC{
   HI_U32       buf_start_addr;
   HI_U32       chan_num_data_size;//rsv[31:22],Channel_num[21:16],Desc_size[15:0]
   HI_U32       buf_len;
   DESC_WORD4   DescAttr;
}PLCIPHER_DESC_S;

typedef struct hiPLCIPHER_DESC_MGR{
    HI_U32 InDescWPtr;
    HI_U32 InDescRPtr;
    HI_U32 InDescStartPhyAddr;
    HI_U8* pu8InDescStartVirAddr;
    HI_U32 OutDescWPtr;
    HI_U32 OutDescRPtr;
    HI_U32 OutDescStartPhyAddr;
    HI_U8* pu8OutDescStartVirAddr;
    HI_U32 LastChanNum;

}PLCIPHER_DESC_MGR_S;

typedef struct
{
    HI_U32  BufPhyAddr;
    HI_U32  BufSmmuAddr;
    HI_U32  BufVirAddr;
    HI_U32  BufLen;
}PLCIPHER_DATA_BUF_S;

typedef struct DESCR_CHAIN
{
   U_DESCR_CHAIN_0  descr0;
   HI_U32           slice_address;
   U_SOC_DEFINE     soc_define;
   HI_U32           user_define_check_code;
}DESCR_CHAIN;

typedef struct hiPLCIPHER_OSR_CHN_S
{
    HI_BOOL Secure;
    HI_U32  ChanID;
    HI_U32  DescBaseAddr;
    HI_U32  InPhyAddr;
    HI_U32  OutPhyAddr;
    HI_U32  DataLen;
    HI_TEE_PLCIPHER_KEY_EVENODD_E enKeyEvenOdd;
    DESCR_CHAIN* pstDesc;
    HI_U32  OddCW[4];
    HI_U32  EvenCW[4];
    HI_U32  IV[4];
    HI_TEE_PLCIPHER_ATTR_S stAttr;
    struct plcipher_mutex LockChn;
}PLCIPHER_ChanInfo_S;

typedef struct hiPlcipher_Set_S
{
    HI_U32                      IoBase;
    HI_U32                      MmuIoBase;

    PLCIPHER_ChanInfo_S         PLChanInfo[PLCIPHER_CHAN_NUM];
    HI_U32                      PLChanCnt;
    struct plcipher_mutex       LockAllChn;
    DECLARE_BITMAP(ChnBitmap, PLCIPHER_CHAN_NUM);
}Plcipher_Set_S;

#define PLCIPHER_DRV_CHECK_CHANID(CHANID) \
    do {  \
        if (CHANID < PLCIPHER_SEC_CHAN_OFFSET || CHANID >= PLCIPHER_CHAN_NUM)\
        {\
            TEE_PLCIPHER_LOG_PrintInfo("CHANID invalid");\
            TEE_PLCIPHER_LOG_PrintU32(CHANID);\
            TEE_PLCIPHER_PrintErrCode(HI_TEE_ERR_INVALID_PARAM);\
            return HI_TEE_ERR_INVALID_PARAM; \
        } \
    } while (0)

#define PL_USECS_PER_SEC   1000000
static HI_VOID inline plcipher_wait_us(HI_U32 usec)
{
    TEE_DRV_DelayUs(usec);
}

static HI_VOID inline plcipher_wait_ms(HI_U32 msec)
{
    plcipher_wait_us(1000 * msec);
}

#endif      /* __DRV_PLCIPHER_DEFINE_H__ */
