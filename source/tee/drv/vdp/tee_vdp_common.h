/***********************************************************************************
*              Copyright 2004 - 2015, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :
* Description:
*
* History:
* Version      Date         Author        DefectNum    Description
* main\1    20151012    NA                 NULL      Create this file.
***********************************************************************************/

#ifndef __TEE_VDP_COMMON_EXT_H__
#define __TEE_VDP_COMMON_EXT_H__

#define WATERMARK_TYPE_SHIFT      16
#define VMX_HANDLE_PREFIX  HI_TEE_VWM_TYPE_VERIMATRIX << WATERMARK_TYPE_SHIFT
#define NEXTGUARD_HANDLE_PREFIX  HI_TEE_VWM_TYPE_NEXGUARD << WATERMARK_TYPE_SHIFT

#define HI_DBG_VDP(fmt...)      HI_TEE_DBG_PRINT(HI_MODULE_ID_VO, fmt)
#define HI_FATAL_VDP(fmt...)    HI_TEE_FATAL_PRINT(HI_MODULE_ID_VO, fmt)
#define HI_ERR_VDP(fmt...)      HI_TEE_ERR_PRINT(HI_MODULE_ID_VO, fmt)
#define HI_WARN_VDP(fmt...)     HI_TEE_WARN_PRINT(HI_MODULE_ID_VO, fmt)
#define HI_INFO_VDP(fmt...)     HI_TEE_INFO_PRINT(HI_MODULE_ID_VO, fmt)

#define ABS(x)           (((x) < 0) ? -(x) : (x))
#define MAX(a, b)         (( (a) < (b) ) ?  (b) : (a))
#define MIN(a, b)         (( (a) > (b) ) ?  (b) : (a))


#define CHECK_NULL_POINTER(ptr) \
{                                \
    if (HI_NULL == (ptr))                    \
    {                            \
        HI_ERR_VDP("WIN Input null pointer!\n"); \
        return HI_TEE_ERR_INVALID_PARAM;  \
    }                             \
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /* __TEE_DMX_HELPER_H__ */
