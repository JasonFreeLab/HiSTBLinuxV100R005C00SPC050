/******************************************************************************
 *
 *             Copyright 2009 - 2009, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 *
 ******************************************************************************
 * File Name     : hi_adp_memmng.h
 * Description   : 内存管理头文件
 *
 * History       :
 * Version     Date        Author      DefectNum    Modification:
 * 1.1         2009-2-27   q63946      NULL         Created file
 *
 ******************************************************************************/
#ifndef __HI_ADP_MEMMNG_H__
#define __HI_ADP_MEMMNG_H__

#include "hi_type.h"
#include "hi_unf_version.h"
#include "hi_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

//#define HI_MEMORY_DEBUG
#ifdef HI_ADVCA_FUNCTION_RELEASE
#undef HI_MEMORY_DEBUG
#endif

/*----------------------------------------------*
 * routine prototypes
 *----------------------------------------------*/

/** @defgroup hi_adpt_memmng_api 内存管理适配层api接口
*   @ingroup H1
*   @brief 详细描述内存管理适配层的API函数
*   @{  */

/**
\brief 申请内存
\attention \n
无
\param[in] u32ModId 模块ID
\param[in] u32Size 待申请内存的大小
\param[in] pszFileName 调用该接口的文件名，可以使用"__FILE__"
\param[in] u32LineNo 调用该接口的文件所在行，可以使用"__LINE__"

\retval ::申请到的内存首地址
\retval ::HI_NULL 申请内存失败

\see \n
无
*/
HI_VOID *HI_MemMng_MallocD(const HI_U32 u32ModId,const HI_U32 u32Size,
                           const HI_CHAR *pszFileName, const HI_U32 u32LineNo);

/**
\brief 释放内存
\attention \n
无
\param[in] u32ModId 模块ID
\param[in] pvMemAddr 内存首地址
\param[in] pszFileName 调用该接口的文件名，可以使用"__FILE__"
\param[in] u32LineNo 调用该接口的文件所在行，可以使用"__LINE__"

\retval ::HI_SUCCESS 释放成功
\retval ::HI_LOG_EPAERM 模块ID错误
\retval ::HI_FAILURE 地址错误

\see \n
无
*/
HI_S32 HI_MemMng_Free(const HI_U32 u32ModId,const HI_VOID* pvMemAddr,
                      const HI_CHAR *pszFileName, const HI_U32 u32LineNo);

/** @} */  /*! <!-- API declaration end */

/*----------------------------------------------*
 * macros
 *----------------------------------------------*/

#ifdef HI_MEMORY_DEBUG

/*****************************************************************************
 * Function     : HI_MEMMNG_MALLOC
 * Description  : 申请内存
 * Input        : enModId,模块ID
 *                u32Size,待申请内存大小
 * Output       : None
 * Return       : HI_VOID *,申请到的内存首地址，空为未申请到
 * Data Accessed: None
 * Data Updated : None
 * Others       : None
 *****************************************************************************/
#define HI_MEMMNG_MALLOC(u32ModId,u32Size)   \
    HI_MemMng_MallocD((u32ModId),(u32Size), (const HI_CHAR *)__FILE__, __LINE__)

/*****************************************************************************
 * Function     : HI_MEMMNG_REALLOC
 * Description  : 申请内存
 * Input        : enModId,模块ID
                : pSrcMem 源内存地址.
 *                u32Size,待申请内存大小
 * Output       : None
 * Return       : HI_VOID *,申请到的内存首地址，空为未申请到
 * Data Accessed: None
 * Data Updated : None
 * Others       : None
 *****************************************************************************/
#define HI_MEMMNG_REALLOC(u32ModId,pSrcMem, u32Size)   \
    HI_MemMng_ReallocD((u32ModId), (pSrcMem), (u32Size), (const HI_CHAR *)__FILE__, __LINE__)

/*****************************************************************************
 * Function     : HI_MEMMNG_FREE
 * Description  : 释放内存
 * Input        : enModId,模块ID
 *                pvMemAddr,内存首地址
 * Output       : None
 * Return       : HI_S32
 * Data Accessed: None
 * Data Updated : None
 * Others       : None
 *****************************************************************************/
#define HI_MEMMNG_FREE(u32ModId,pvMemAddr)   \
    HI_MemMng_Free((u32ModId),(pvMemAddr), (const HI_CHAR *)__FILE__, __LINE__)

#else
#define HI_MEMMNG_MALLOC(u32ModId,u32Size)    malloc((u32Size))
#define HI_MEMMNG_REALLOC(u32ModId,pSrcMem, u32Size)   realloc((pSrcMem), (u32Size))
#define HI_MEMMNG_FREE(u32ModId,pvMemAddr)   free((pvMemAddr))
#endif

#ifndef HI_ADVCA_FUNCTION_RELEASE
/*----------------------------------------------*
 * routine prototypes
 *----------------------------------------------*/
/*
memprint
    -mod [0~52|all] ;打印指定模块分配内存情况
*/

#if (UNF_VERSION_CODE >= UNF_VERSION(3, 1))
HI_S32 HI_CMD_MemMng_Queue(HI_PROC_SHOW_BUFFER_S * pstBuf, HI_VOID *pPrivData);
#else
HI_S32  HI_CMD_MemMng_Queue(HI_U32 u32Handle,int argc, const char* argv[]);
#endif
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*__HI_ADP_MEMMNG_H__*/

