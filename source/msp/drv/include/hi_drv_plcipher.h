/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     :hi_drv_plcipher.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#ifndef __HI_DRV_PLCIPHER_H__
#define __HI_DRV_PLCIPHER_H__

#include "hi_type.h"
#include "hi_unf_payloadcipher.h"
#include "hi_unf_hdcp.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifdef PLCIPHER_TEE_SUPPORT
#define PLCIPHER_CHAN_NUM      4
#else
#define PLCIPHER_CHAN_NUM      8
#endif

#ifdef PLCIPHER_V1
#define PLCIPHER_MIN_SIZE_PRE_DESC   (188*16)
#else
#define PLCIPHER_MIN_SIZE_PRE_DESC   (188)
#endif
#define PLCIPHER_MAX_SIZE_PRE_DESC   (47*1024)

#define PLCIPHER_INVALID_CHN        (0xffffffff)
#define PLCIPHER_KEY_SIZE    16
#define PLCIPHER_DSC_NUM     512     //512*47k = 24M


#define HI_FATAL_PLCIPHER(fmt...)             HI_FATAL_PRINT(HI_ID_PLCIPHER, fmt)
#define HI_ERR_PLCIPHER(fmt...)               HI_ERR_PRINT(HI_ID_PLCIPHER, fmt)
#define HI_WARN_PLCIPHER(fmt...)              HI_WARN_PRINT(HI_ID_PLCIPHER, fmt)
#define HI_INFO_PLCIPHER(fmt...)              HI_INFO_PRINT(HI_ID_PLCIPHER, fmt)
#define HI_DEBUG_PLCIPHER(fmt...)             HI_DBG_PRINT(HI_ID_PLCIPHER, fmt)


typedef struct  hiPLCIPHER_HANDLE_S
{
    HI_HANDLE Handle;
    HI_UNF_PLCIPHER_ATTR_S stPlCipherAtts;
}PLCIPHER_CONFIG_S;

typedef struct  hiPLCIPHER_DATA_S
{
    HI_HANDLE CIHandle;
    HI_U32 ScrPhyAddr;
    HI_U32 DestPhyAddr;
    HI_U32 u32DataLength;
}PLCIPHER_DATA_S;

typedef struct hiPLCIPHER_SetKey
{
    HI_HANDLE CIHandle;
    HI_BOOL bIsCWOrIV;
    HI_UNF_PLCIPHER_KEY_EVENODD_E enEvenOdd;
    HI_U8   Key[PLCIPHER_KEY_SIZE];
}PLCIPHER_SetKey;

typedef union CW_SET_U{
struct{
    HI_U32  rsv1:8;
    HI_U32  sw_cw_odd_even: 1;
    HI_U32  sw_cw_channel_id: 4;
    HI_U32  rsv2:3;
    HI_U32  sw_cw_type: 8;
    HI_U32  sw_iv_sel: 1;
    HI_U32  rsv3:   3;
    HI_U32  case_sw_algo_type_ok:1;
    HI_U32  rsv4: 3;

    }struBits;
    HI_U32 ALL;
}CW_SET_DEF;

typedef union
{
    struct
    {
        HI_U32  crypt_type:1;//0
        HI_U32  cw_odd_even:1;//[1], 0:even, 1: odd
        HI_U32  rsv0: 23;//[24:2], key_id and iv_id and algo_type now is not used
        HI_U32  rec_ts_length:   1;//25
        HI_U32  rsv:5;//[30:26]
        HI_U32  buffer_drop: 1;//31

    }bits;
    HI_U32 u32;
}DESC_WORD4;

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

HI_S32  HI_DRV_PLCIPHER_Init(HI_VOID);
HI_VOID HI_DRV_PLCIPHER_DeInit(HI_VOID);
HI_S32  HI_DRV_PLCIPHER_Open(HI_VOID);
HI_S32  HI_DRV_PLCIPHER_Close(HI_VOID);
HI_S32  HI_DRV_PLCIPHER_CreateHandle(HI_HANDLE* phPLCipher);
HI_S32  HI_DRV_PLCIPHER_DestroyHandle(HI_HANDLE hCipherchn);
HI_S32  HI_DRV_PLCIPHER_GetAttr(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_ATTR_S* pstAttr);
HI_S32  HI_DRV_PLCIPHER_SetAttr(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_ATTR_S* pstAttr);
HI_S32  HI_DRV_PLCIPHER_SetKeyIV(PLCIPHER_SetKey* pstKey);
HI_S32  HI_DRV_PLCIPHER_Encrypt(PLCIPHER_DATA_S *pstCIData);
HI_S32  HI_DRV_PLCIPHER_Decrypt(PLCIPHER_DATA_S *pstCIData);

/* extern for keyaddder */
HI_S32 HI_DRV_PLCIPHER_SetKey(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyType, HI_U8 *pu8Key, HI_U32 u32KeyLen);
HI_S32 HI_DRV_PLCIPHER_SetIV(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyType, HI_U8 *pu8IV, HI_U32 u32IVLen);

HI_VOID HI_DRV_PLCIPHER_Suspend(HI_VOID);
HI_S32  HI_DRV_PLCIPHER_Resume(HI_VOID);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* End of #ifndef __HI_DRV_PLCIPHER_H__*/

