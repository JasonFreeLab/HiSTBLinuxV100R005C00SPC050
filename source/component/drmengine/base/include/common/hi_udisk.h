/*****************************************************************************
 *             Copyright 2009 - 2050, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 ******************************************************************************
 File Name     : hi_udisk.h
Version       : Initial draft
Author        : HiSilicon multimedia software group
Created Date   : 2012-09-19
Last Modified by:
Description   : Application programming interfaces (APIs) of the udisk (UDISK)
Function List :
Change History:
 ******************************************************************************/

/** @defgroup UDISK UDISK(USB Disk)
 * \file
 * \brief Application programming interfaces (APIs) of the USB DISK (UDISK).
 * \brief CNcomment: 该模块提供USB Disk操作的功能:1.获取U盘的及分区属性 2.上报插拔/挂载事件 3.获取某一目录下的文件列表
 */

#ifndef __HI_UDISK_H__
#define __HI_UDISK_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/***************************** Macro Definition ******************************/
/** \addtogroup      UDISK */
/** @{ */  /** <!-- [UDISK] */

#define HI_UDISK_PARAM_MAX_LEN       (300)
#define MAX_UDISK_NAME_LEN           (512)
#define UDISK_MAX_DEV_NUM            (16)
#define UDISK_MAX_TRY_NUM            (20)
#define MAX_DEV_NAME_LEN             (12)

/** @} */  /*! <!-- Macro Definition End */

/** Error Code */
enum
{
    HI_UDISK_ERR_NULL           = HI_FAILURE,
    HI_UDISK_ERR_INVALIDPARA    = -2,
    HI_UDISK_ERR_NOMEM          = -3,
    HI_UDISK_ERR_EXIST          = -4,
    HI_UDISK_ERR_FULL           = -5,
    HI_UDISK_ERR_UNKNOWN_TYPE   = -6,
    HI_UDISK_ERR_NOTEXIST       = -7,
    HI_UDISK_ERR_BUTT
};

/** Disk info */
typedef struct
{
    HI_U64  u64TotalSize;
    HI_U64  u64AvailSize;
    HI_CHAR szVendor[MAX_UDISK_NAME_LEN];
    HI_CHAR szModel[MAX_UDISK_NAME_LEN];
    HI_CHAR szDevPath[MAX_UDISK_NAME_LEN];
    HI_CHAR szMntPath[MAX_UDISK_NAME_LEN];
} HI_UDISK_DISKINFO_S;

/** Disk format */
typedef enum
{
    HI_UDISK_FSTYPE_FAT = 0x0,
    HI_UDISK_FSTYPE_FAT32,
    HI_UDISK_FSTYPE_NTFS,
    HI_UDISK_FSTYPE_EXT2,
    HI_UDISK_FSTYPE_EXT3,

    HI_UDISK_FSTYPE_BUT,
} HI_UDISK_FSTYPE_E;

/** Disk partition info. */
typedef struct
{
    HI_BOOL           bMounted;
    HI_UDISK_FSTYPE_E enFSType; /**<Partition format.*/
    HI_U64            u64TotalSize;
    HI_U64            u64AvailSize;
    HI_CHAR           szDevPath[MAX_UDISK_NAME_LEN]; /**<Partition Device directory.*/
    HI_CHAR           szMntPath[MAX_UDISK_NAME_LEN]; /**<Partition mount directory.*/
} HI_UDISK_PARTITIONINFO_S;

/** File list. */
typedef struct
{
    HI_U32   u32Index;       /**<File index, start from 0. */
    HI_U32   u32Type;        /**<0:DIR, 1:FILE */
    HI_U64   u64Size;        /**<file size, Byte */
    HI_U32   u32CTime;       /**<file created time. */
    HI_CHAR* pszShortName;   /**<file Name, No include path. Read only. */
    HI_CHAR* pszFullName;    /**<full file Name. include path. Read only. */
} HI_UDISK_FILEINFO_S;

/** Mode for browsing directory/files. support Multi modes at the same time.*/
typedef enum
{
    HI_UDISK_SORT_DEFAULT   = 0x00000011, /**<default method.*/
    HI_UDISK_SORT_ASC       = 0x00000001,    /**<Ascend sort.*/
    HI_UDISK_SORT_DESC      = 0x00000002, /**<Descend sort.*/
    HI_UDISK_SORT_NAME      = 0x00000010, /**<Sort by Name.*/
    HI_UDISK_SORT_TIME      = 0x00000020, /**<Sort by time.*/
    HI_UDISK_SORT_SIZE      = 0x00000040, /**<Sort by fileSize.*/
    HI_UDISK_SORT_EXT       = 0x00000080, /**<Sort by file extention name. */

    HI_UDISK_SORT_BUTT
} HI_UDISK_SORT_MODE_E;

/** File filter condtion for browsing.*/
typedef enum
{
    HI_UDISK_FLT_DEFAULT    = 0x00000005, /**<Default mode: UP+SUB,*/
    HI_UDISK_FLT_NODIR      = 0x00000000,   /**<Search result doesn't include andy directory. */
    HI_UDISK_FLT_UPDIR      = 0x00000001,   /**<Search result include Parent directory, that is ".." */
    HI_UDISK_FLT_CURDIR     = 0x00000002,   /**<Search result include current directory, that is "." */
    HI_UDISK_FLT_SUBDIR     = 0x00000004,   /**<Search result include directories.*/
    HI_UDISK_FLT_CASECARE   = 0x00000008, /**<capital/lowercase sensitive */

    HI_UDISK_FLT_BUTT
} HI_UDISK_FILTER_E;

/** Search conditions */
typedef struct
{
    HI_BOOL              bRecursive;    /**<Recursive sub directories */
    HI_UDISK_SORT_MODE_E enSortMode;    /**<Directory sort mode. */
    HI_UDISK_FILTER_E    enFilterType;  /**<File filter conditons.*/
    HI_CHAR*             pFileFilter;   /**<File extentions to list, usage : ".*":(All files)；
                                        "": (No file include)；".mp3": (Only mp3 files)；
                                        ".jpg,.png": (Get jpg and png files.) */
} HI_UDISK_SCAN_S;

typedef struct
{
    HI_UDISK_FILEINFO_S** ppFileList;
    HI_U32                 u32FileNum;
} HI_UDISK_FILELIST_S;

/** Callback event. */
typedef enum
{
    HI_UDISK_EVENT_PLUGIN = 0x0,        /**<Disk plugin.*/
    HI_UDISK_EVENT_PLUGOUT,             /**<Disk plugout. */
    HI_UDISK_EVENT_MOUNTED,             /**<Partition mountd.*/
    HI_UDISK_EVENT_UMOUNTED,            /**<Partition umounted. */
    HI_UDISK_EVENT_FULL,                /**<Partition is full. */
    HI_UDISK_EVENT_ALLPARTMOUNTED,      /**<All partitions on this Disk has been mounted.*/
    HI_UDISK_EVENT_DISKSCANREQUEST,     /**<NTFS partition need run chkntfs command to scan.*/
    HI_UDISK_EVENT_DISKSCANCOMPLETE,
    HI_UDISK_EVENT_UNKNOWNFILESYS,      /**< Unknow partition format, need format/partition disk firstly.*/
    HI_UDISK_EVENT_ROPARTITION,
    HI_UDISK_EVENT_QUERY_INTERRUPTFLAG, /**< Query interrupt flag. */
    HI_UDISK_EVENT_BUTT
} HI_UDISK_EVENT_E;

/**
 \brief  Callback function
 \attention \n
 \param[in] HI_UDISK_EVENT_E : event type.
 \param[in] pParam : Parameter to the event type. HI_UDISK_EVENT_PARAM_XXXX_S;
 \param[in] pPrivate : reserve default HI_NULL

 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE

 \see \n
::HI_UDISK_EVENT_PARAM_PLUG_S \n
::HI_UDISK_EVENT_PARAM_MOUNT_S \n
::HI_UDISK_EVENT_PARAM_FULL_S
 */
typedef HI_S32 (*HI_UDISK_EVENT_CALLBACK)(HI_UDISK_EVENT_E enEvent,
                                          HI_VOID* pParam,
                                          HI_VOID* pPrivate);

/** for Disk PLUGIN/PLUGOUT event.*/
typedef struct
{
    HI_U32  u32DiskIndex;
    HI_CHAR szMntPath[MAX_UDISK_NAME_LEN];  /**<Mount path */
} HI_UDISK_EVENT_PARAM_PLUG_S;

/**  for Disk MOUNTED/UNMOUNTED event.*/
typedef struct
{
    HI_U32  u32DiskIndex;
    HI_U32  u32PartitionIndex;
    HI_CHAR szMntPath[MAX_UDISK_NAME_LEN];  /**<Mount path */
} HI_UDISK_EVENT_PARAM_MOUNT_S;

/** for Disk FULL condtions. */
typedef struct
{
    HI_U32 u32DiskIndex;
    HI_U32 u32PartitionIndex;
} HI_UDISK_EVENT_PARAM_FULL_S;

typedef struct
{
    HI_CHAR szDevPath[MAX_UDISK_NAME_LEN];
} HI_UDISK_EVENT_PARAM_SCAN_S;

typedef struct
{
    HI_U32 u32ParitionNum;
    HI_CHAR szDevPath[UDISK_MAX_DEV_NUM][MAX_DEV_NAME_LEN];
} HI_UDISK_EVENT_PARAM_UNKOWNFILESYS_S;

typedef struct hiUDISK_INIT_PARAM_S
{
    HI_BOOL bForceMountNTFS; /*whether use -o force item to mount NTFS filesystem.*/
    HI_BOOL bUseblkidtool; /*whether use blkid tool to detect udisk format.*/
    HI_CHAR acUdiskRoot[HI_UDISK_PARAM_MAX_LEN];    /**<The root path of USB pen Mounted */
    HI_CHAR acMountParam[HI_UDISK_PARAM_MAX_LEN];   /**<Mount parameter, eg. "codepage=936,iocharset=utf8" */
} HI_UDISK_INIT_PARAM_S;

/******************************* API declaration *****************************/
/** \addtogroup     UDISK  */
/** @{ */  /** <!-- [UDISK] */

/**
 \brief  UDISK Initialize.
 \attention \n
 \param[in] pUdiskRoot : UDISK mount root, such as "/mnt" or "/tmp"
 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE
 */
HI_S32 HI_UDISK_Init(HI_UDISK_INIT_PARAM_S* pstInitParam);

/**
 \brief  UDISK Deinit.
 \attention \n
 \param[in]
 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE
 */
HI_S32 HI_UDISK_Deinit(HI_VOID);

/**
 \brief  Get UDISK mount root.
 \attention \n
 \param[in]
 \retval  ::Udisk mount root.
 \retval  ::HI_FAILURE

 \see \n
::HI_UDISK_Init
 */
HI_CHAR* HI_UDISK_GetRoot(HI_VOID);

/**
 \brief  Get the number of Disks mounted.
 \attention \n
 \param[out] pu32DiskNum  : The Number of Disks mounted.

 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE

 \see \n
::HI_UDISK_GetDiskInfo
 */
HI_S32 HI_UDISK_GetDiskNum(HI_U32* pu32DiskNum);

/**
 \brief  Get Disk info
 \attention \n
 \param[in] u32DiskIndex : Disk Index，start from index 0.
 \param[out] pDiskInfo   : Disk info.

 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE

 \see \n
::HI_UDISK_GetDiskNum
 */
HI_S32 HI_UDISK_GetDiskInfo(HI_U32 u32DiskIndex, HI_UDISK_DISKINFO_S* pDiskInfo);

/**
 \brief  Get the Partition numbers of the Disk.
 \attention \n
 \param[in] u32DiskIndex  : Disk Index
 \param[out] pu32PartitionNum  : Partition Numbers.

 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE

 \see \n
::HI_UDISK_GetPartitionInfo
 */
HI_S32 HI_UDISK_GetPartitionNum(HI_U32 u32DiskIndex, HI_U32* pu32PartitionNum);

/**
 \brief  Get the Given Partition info.
 \attention \n
 \param[in] u32DiskIndex  : Disk Index,
 \param[in] u32PartitionIndex  : Partition Index.
 \param[out] pPartitionInfo  : Partition info.

 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE

 \see \n
::HI_UDISK_GetPartitionNum
 */
HI_S32 HI_UDISK_GetPartitionInfo(HI_U32 u32DiskIndex, HI_U32 u32PartitionIndex,
                                 HI_UDISK_PARTITIONINFO_S* pPartitionInfo);

/**
 \brief  Format the Partition
 \attention : Don't support currently.\n
 \param[in] u32DiskIndex  : Disk index.
 \param[in] u32PartitionIndex  : Partition Index
 \param[in] enFSType  : Disk file system format.

 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE

 \see \n
::HI_UDISK_GetDiskNum \n
::HI_UDISK_GetPartitionNum
 */
HI_S32 HI_UDISK_FormatPartition(HI_U32 u32DiskIndex, HI_U32 u32PartitionIndex, HI_UDISK_FSTYPE_E enFSType);

/**
 \brief  Get the file list of the Given directory.
 \attention \n
 \param[in] u32Pid : The progress id of the object calling this function.
 \param[in] pszDir  :  The Given dirctory.
 \param[in] pScanOpt  : Scan option.
 \param[out] pFileList  : File list. the memory is allocated by driver. the caller should call
                        HI_UDISK_FreeFileList() to free the memory to avoid memory leak.

 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE

 \see \n
::HI_UDISK_FreeFileList
 */
HI_S32 HI_UDISK_GetFileList(HI_U32 u32Pid, HI_CHAR* pszDir,
                            HI_UDISK_SCAN_S*      pScanOpt,
                            HI_UDISK_FILELIST_S* pFileList);

/**
 \brief  Free the memory allcated for HI_UDISK_GetFileList() API.
 \attention \n
 \param[in] pFileList  : pointer to the File list

 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE

 \see \n
::HI_UDISK_GetFileList
 */
HI_S32 HI_UDISK_FreeFileList(HI_UDISK_FILELIST_S* pFileList);

/**
 \brief  Register Callback function for UDisk event.
 \attention \n
 \param[in] enEvent  : event type.
 \param[in] pCallbackFunc  : Callback function for enEvent.
 \param[in] pPrivate  : Private Structure. Directly Pass through to the Callback function.
 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE

 \see \n
::HI_UDISK_UnRegisterEventCallback
 */
HI_S32 HI_UDISK_RegisterEventCallback(HI_UDISK_EVENT_E     enEvent,
                                      HI_UDISK_EVENT_CALLBACK pCallbackFunc,
                                      HI_VOID*                pPrivate);

/**
 \brief  UnRegister the callback event.
 \attention \n
 \param[in] enEvent  : Event Type.
 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE
 \see \n
::HI_UDISK_RegisterEventCallback
 */
HI_S32 HI_UDISK_UnRegisterEventCallback(HI_UDISK_EVENT_E enEvent);

/**
 \brief
 \attention \n
 \param[in] u32DiskIndex  : Disk Index
 \param[in] u32PartitionIndex  : Partition Index
 \param[in] bReport  : Whether report to upper level.
 \param[in] u64WaterLine  :
 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE

 \see \n
 */
HI_S32 HI_UDISK_SetFullReport(HI_U32 u32DiskIndex, HI_U32 u32PartitionIndex, HI_BOOL bReport, HI_U64 u64WaterLine);

/**
 \brief     Mount NTFS file system by -o force item or not.
 \attention \n
 \param[in] bForceMount: Use -o force item to mount NTFS or not.
 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE
 \see \n
 */
HI_S32 HI_UDISK_ScanAndMount(HI_BOOL bForceMount);

/**
 \brief     UnMount all file system.
 \attention \n
 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE
 \see \n
 */
HI_VOID HI_UDISK_UmountAllDisk(HI_VOID);

/**
 \brief  Get the file num of the Given directory.
 \attention \n
 \param[in] pszDir  :  The Given dirctory.
 \param[in] pScanOpt  : Scan option.
 \param[out] pu32FileNum  : File num.

 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE

 \see \n
::HI_UDISK_FreeFileList
 */
HI_S32 HI_UDISK_GetFileNum(HI_CHAR* pszDir,
                           HI_UDISK_SCAN_S*      pScanOpt,
                           HI_U32* pu32FileNum);

/**
 \brief  Get the file list of the Given directory from u32StartIndex to u32EndIndex.
 \attention \n
 \param[in] u32Pid : The progress id of the object calling this function.
 \param[in] pszDir  :  The Given dirctory.
 \param[in] pScanOpt  : Scan option.
 \param[in] u32StartIndex : get file list from here.
 \param[in] u32FileCount :  file count being got.
 \param[out] pFileList  : File list. the memory is allocated by driver. the caller should call
                        HI_UDISK_FreeFileList() to free the memory to avoid memory leak.

 \retval  ::HI_SUCCESS
 \retval  ::HI_FAILURE

 \see \n
::HI_UDISK_FreeFileList
 */
HI_S32 HI_UDISK_GetFileListWithIndex(HI_U32 u32Pid, HI_CHAR* pszDir,
                                     HI_UDISK_SCAN_S*      pScanOpt,
                                     HI_U32 u32StartIndex, HI_U32 u32FileCount,
                                     HI_UDISK_FILELIST_S* pFileList);

/** @} */  /*! <!-- API declaration end */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UDISK_H__ */
