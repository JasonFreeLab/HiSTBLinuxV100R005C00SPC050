/******************************************************************************
 Copyright (C), 2015-2025, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
  File Name     : svr_proc.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/08/24
  Description   : Common apis for hisilicon system.
  History       :
  1.Date        : 2015/08/24
    Author      :
    Modification: Created file

*******************************************************************************/

#ifndef SVR_PROC_H__
#define SVR_PROC_H__

#include "hi_type.h"

#ifdef __cplusplus
extern "C"{
#endif /* End of #ifdef __cplusplus */

/*******************************Structure declaration *****************************/
/** @addtogroup     COMMON */
/** @{ */ /** <!--  [COMMON] */

/** Defines user mode proc show buffer */
/**CNcomment: 用户态PROC buffer定义 */
typedef struct hiSVR_PROCSHOW_BUFFER_S
{
    HI_U8* pu8Buf;                  /**<Buffer address*/ /**<CNcomment: Buffer地址 */
    HI_U32 u32Size;                 /**<Buffer size*/     /**<CNcomment: Buffer大小 */
    HI_U32 u32Offset;               /**<Offset*/         /**<CNcomment: 打印偏移地址 */
} SVR_PROCSHOW_BUFFER_S;

/** Proc show function */
/**CNcomment: Proc信息显示回调函数 */
typedef HI_S32 (* SVR_PROCSHOW_FN)(SVR_PROCSHOW_BUFFER_S * pstBuf, HI_VOID *pPrivData);

/** Proc command function */
/**CNcomment: Proc控制回调函数 */
typedef HI_S32 (* SVR_PROCCMD_FN)(SVR_PROCSHOW_BUFFER_S * pstBuf, HI_U32 u32Argc, HI_U8 *pu8Argv[], HI_VOID *pPrivData);

/** Defines user mode proc entry */
/**CNcomment: 用户态PROC入口定义 */
typedef struct hiSVR_PROCENTRY_S
{
    HI_CHAR *pszEntryName;          /**<Entry name*/            /**<CNcomment: 入口文件名 */
    HI_CHAR *pszDirectory;          /**<Directory name. If null, the entry will be added to /proc/hisi directory*/
                                    /**<CNcomment: 目录名，如果为空，将创建到/proc/hisi目录下 */
    SVR_PROCSHOW_FN pfnShowProc;    /**<Proc show function*/    /**<CNcomment: Proc信息显示回调函数 */
    SVR_PROCCMD_FN pfnCmdProc;      /**<Proc command function*/ /**<CNcomment: Proc控制回调函数 */
    HI_VOID *pPrivData;             /**<Private data*/          /**<CNcomment: Buffer地址 */
}SVR_PROCENTRY_S;

#ifndef __KERNEL__
#include <time.h>

/**
@brief Register one module to manager. CNcomment:模块注册，用于管理 CNend
@attention Before manager someone module, calling this interface. CNcomment:如需管理模块，用此接口先注册 CNend
@param[in] pszModuleName The module name CNcomment:模块名称 CNend
@param[in] u32ModuleID   The module ID. CNcomment:模块ID CNend
@retval ::HI_SUCCESS Success CNcomment:成功 CNend
@retval ::HI_FAILURE Failure CNcomment:失败 CNend
@see \n
N/A CNcomment:无 CNend
*/
HI_S32 SVR_MODULE_Register(HI_U32 u32ModuleID, const HI_CHAR * pszModuleName);

/**
@brief Register one moudle by name. CNcomment:模块注册，ID由系统分配 CNend
@attention Before manager someone module, calling this interface. CNcomment:如需管理模块，用此接口先注册 CNend
@param[in] pszModuleName The module name CNcomment:模块名称 CNend
@param[out] pu32ModuleID The module id allocated by system. CNcomment:系统分配的模块ID CNend
@retval ::HI_SUCCESS Success CNcomment:成功 CNend
@retval ::HI_FAILURE Failure CNcomment:失败 CNend
@see \n
N/A CNcomment:无 CNend
*/
HI_S32 SVR_MODULE_RegisterByName(const HI_CHAR * pszModuleName, HI_U32* pu32ModuleID);

/**
@brief UnRegister one module to trace. CNcomment:模块移除 CNend
@attention Before stopping to manage someone module, calling this interface. CNcomment:不需要管理此模块时，使用此接口移除模块 CNend
@param[in] u32ModuleID The module ID. CNcomment:模块ID CNend
@param[out] None CNcomment:无 CNend
@retval ::HI_SUCCESS Success CNcomment:成功 CNend
@retval ::HI_FAILURE Failure CNcomment:失败 CNend
@see \n
N/A CNcomment:无 CNend
*/
HI_S32 SVR_MODULE_UnRegister(HI_U32 u32ModuleID);

/**
@brief User mode proc cretea directory. CNcomment:用户态proc创建目录 CNend
@attention You need register module before calling this API. Only support create one level directory. CNcomment:需要先注册模块，只支持创建一级目录 CNend
@param[in] pszName The directory name. CNcomment:目录名 CNend
@param[out] None CNcomment:无 CNend
@retval ::HI_SUCCESS Success CNcomment:成功 CNend
@retval ::HI_FAILURE Failure CNcomment:失败 CNend
@see \n
N/A CNcomment:无 CNend
*/
HI_S32 SVR_PROC_AddDir(const HI_CHAR *pszName);

/**
@brief User mode proc remove directory. CNcomment:用户态proc删除目录 CNend
@attention It will return fail if there are entries in the directory. CNcomment:如果目录下还有入口文件,将会删除失败 CNend
@param[in] pszName The directory name. CNcomment:目录名 CNend
@retval ::HI_SUCCESS Success CNcomment:成功 CNend
@retval ::HI_FAILURE Failure CNcomment:失败 CNend
@see \n
N/A CNcomment:无 CNend
*/
HI_S32 SVR_PROC_RemoveDir(const HI_CHAR *pszName);

/**
@brief User mode proc add entry. CNcomment:用户态proc创建入口 CNend
@attention \n
N/A CNcomment: 无 CNend
@param[in] u32ModuleID Module ID. CNcomment:模块ID CNend
@param[in] pstEntry Parameter of entry. CNcomment:创建入口参数 CNend
@retval ::HI_SUCCESS Success CNcomment:成功 CNend
@retval ::HI_FAILURE Failure CNcomment:失败 CNend
@see \n
N/A CNcomment:无 CNend
*/
HI_S32 SVR_PROC_AddEntry(HI_U32 u32ModuleID, const SVR_PROCENTRY_S* pstEntry);

/**
@brief User mode proc remove entry. CNcomment:用户态proc删除入口 CNend
@attention \n
N/A CNcomment: 无 CNend
@param[in] u32ModuleID Module ID. CNcomment:模块ID CNend
@param[in] pstEntry Parameter of entry. CNcomment:删除入口参数 CNend
@retval ::HI_SUCCESS Success CNcomment:成功 CNend
@retval ::HI_FAILURE Failure CNcomment:失败 CNend
@see \n
N/A CNcomment:无 CNend
*/
HI_S32 SVR_PROC_RemoveEntry(HI_U32 u32ModuleID, const SVR_PROCENTRY_S* pstEntry);

/**
@brief User mode proc print function. CNcomment:用户态proc打印内容的函数 CNend
@attention \n
N/A CNcomment: 无 CNend
@param[in] pstBuf Output buffer parameter. CNcomment:输出buffer参数 CNend
@param[in] pFmt Format parameter. CNcomment:打印格式化参数 CNend
@retval ::HI_SUCCESS Success CNcomment:成功 CNend
@retval ::HI_FAILURE Failure CNcomment:失败 CNend
@see \n
N/A CNcomment:无 CNend
*/
HI_S32 SVR_PROC_Printf(SVR_PROCSHOW_BUFFER_S *pstBuf, const HI_CHAR *pFmt, ...);

/** @} */ /** <!-- ==== API declaration end ==== */

#endif /* endif __KERNEL__ */
#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */
#endif /* SVR_PROC_H__ */
