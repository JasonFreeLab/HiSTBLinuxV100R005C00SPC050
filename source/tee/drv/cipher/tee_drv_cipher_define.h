/******************************************************************************
 *
 * Copyright (C), 2004-2014, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : drv_cipher_define.h
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2013-12-28
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * ******************************************************************************/
#ifndef __TEE_CIPHER_DEFINE_H__
#define __TEE_CIPHER_DEFINE_H__

#include "hi_type.h"
#include "hi_tee_cipher.h"
#include "tee_drv_cipher.h"
#include "hi_tee_debug.h"
#include "tee_drv_common.h"

#ifdef CFG_HI_TEE_TEST_SUPPORT
#define HI_CIPHER_TEST
#define HI_CIPHER_DEBUG
#endif

#define __CIPHER_DEBUG_VERSION__ /* when release cipher SW, mask it */

#define HASH_PAD_MAX_LEN	(64)
#define HASH_MAX_SIZE       (0x100000-HASH_PAD_MAX_LEN)
#define SECURE_MEM_CIPHER_MAX_SIZE          (0x100000-16)
#define CIPHER_IRQ_NUMBER          		(126 + 32)       /*Hi3798m*/
#define CIPHER_WAIT_IDLE_TIMES 1000

#define TASK_QUEUE_IDLE 			(0)
#define TASK_QUEUE_BUSY 			(1)

#define MEM_LENGTH_ERROR    		(1)
#define AHB_BUS_ERROR       		(2)

#define CIPHER_MAX_LIST_NUM  		(128)

#define CI_IV_SIZE       			(16)  /* max 128bit */
#define CI_KEY_SIZE      			(32)  /* max 256bit */


#define CI_BUF_LIST_FLAG_DUMMY_BIT  (20)
#define CI_BUF_LIST_FLAG_IVSET_BIT  (21)
#define CI_BUF_LIST_FLAG_EOL_BIT    (22)

#define SECURE_MEM 0
#define NON_SECURE_MEM 1

typedef struct hiCI_BUF_LIST_ENTRY_S
{
    HI_U32  u32DataAddr;    /* Phy Addr */
    HI_U32  u32Flags;       /* bit21: iv_set_flag, bit22: end_of_list_flag */
    HI_U32  U32DataLen;     /* bit0~bit19, total 20 bit */
    HI_U32  u32IVStartAddr; /* if iv_set_flag == 1, this is the IV addr */
} CI_BUF_LIST_ENTRY_S;

/*************************** Structure Definition ****************************/
/** \addtogroup      CIPHER */
/** @{ */  /** <!-- [CIPHER] */

#if 0
/*media memory map structure*/
typedef struct hiMMZ_BUFFER_S
{
    unsigned int u32StartVirAddr;
    unsigned int u32StartPhyAddr;
    unsigned int u32StartSmmuAddr;
    unsigned int u32Size;
}MMZ_BUFFER_S;
#endif

#define HI_PRINT tee_hal_printf
#define HI_ERR_CIPHER(fmt...)               HI_TEE_ERR_PRINT(HI_MODULE_ID_CIPHER, fmt) //tee_hal_printf(fmt)
#define HI_INFO_CIPHER(fmt...)              HI_TEE_INFO_PRINT(HI_MODULE_ID_CIPHER, fmt)

#ifdef HI_CIPHER_DEBUG
#define HI_DBG_CIPHER(fmt...)             tee_hal_printf(fmt)
#else
#define HI_DBG_CIPHER(fmt...)
#endif

#define HI_PRINT_HEX(name, str, len) \
{\
    HI_U32 _i = 0;\
    HI_U32 _val; \
    HI_U8 *_str = (HI_U8*)str;\
	if (_str != HI_NULL) \
    {\
		HI_PRINT("[%s]:\n", name);\
		for ( _i = 0 ; _i < (len); _i+=4 )\
		{\
			_val  = *((_str)+_i+3);\
			_val |= *((_str)+_i+2) << 8;\
			_val |= *((_str)+_i+1) << 16;\
			_val |= *((_str)+_i+0) << 24;\
			if( (_i % 16 == 0) && (_i != 0)) HI_PRINT("\n");\
			HI_PRINT("%x ", _val);\
		}\
		HI_PRINT("\n");\
	}\
}

#define CIPHER_READ_REG(reg, result) ((result) = *(volatile unsigned int *)(tee_hal_phys_to_virt(reg)))
#define CIPHER_WRITE_REG(reg, data) (*((volatile unsigned int *)(tee_hal_phys_to_virt(reg))) = (data))

#define CIPHER_MSLEEP(msec) TEE_DRV_DelayUs(msec * 10) //10us

void *sw_memcpy(void *dst, unsigned dstlen, const void *src, unsigned len);
void *sw_memset(void *dst, unsigned val, unsigned len);
int sw_memcmp(const void *a, const void *b, unsigned len);

#endif


