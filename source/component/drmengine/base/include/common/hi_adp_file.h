/******************************************************************************
 *
 *             Copyright 2009 - 2009, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 *
 ******************************************************************************
 * File Name     : hi_adp_file.h
 * Description   : 文件操作适配头文件
 *
 * History       :
 * Version     Date        Author      DefectNum    Modification:
 * 1.1         2009-2-27   q63946      NULL         Created file
 *
 ******************************************************************************/

#ifndef __HI_ADPT_FILE_H__
#define __HI_ADPT_FILE_H__
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/stat.h>

#include "hi_type.h"
#include "hi_adp_interface.h"
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#if HI_OS_TYPE == HI_OS_WIN32
#include <fcntl.h>
#endif

/*----------------------------------------------*
 * types
 *----------------------------------------------*/

typedef struct HIstat {
#if HI_OS_TYPE == HI_OS_LINUX
    HI_S64 st_dev;      /* device */

/*    HI_U16  __pad1;*/
    HI_U32  st_ino;      /* inode */
    HI_U32  st_mode;
    HI_U32  st_nlink;
    HI_U32  st_uid;
    HI_U32  st_gid;
    HI_S64  st_rdev;      /* device */

/*    HI_U16  __pad2;*/
    HI_S32       st_size;

    HI_S32  st_blksize;  /* blocksize for filesystem I/O */
    HI_S32  st_blocks;   /* number of blocks allocated */

    #ifdef  st_atime
    #undef  st_atime
    #undef  st_mtime
    #undef  st_ctime
    #undef  st_atimensec
    #undef  st_mtimensec
    #undef  st_ctimensec
    #endif
    HI_S32  st_atime;            /* Time of last access.  */
    HI_U32  st_atimensec;    /* Nscecs of last access.  */
    HI_S32  st_mtime;            /* Time of last modification.  */
    HI_U32  st_mtimensec;    /* Nsecs of last modification.  */
    HI_S32  st_ctime;            /* Time of last status change.  */
    HI_U32  st_ctimensec;    /* Nsecs of last status change.  */
    HI_U32  __unused4;
    HI_U32  __unused5;
#elif HI_OS_TYPE == HI_OS_WIN32
    HI_U32  st_dev;      /* device */
    HI_U16  st_ino;      /* inode */
    HI_U16  st_mode;
    HI_S16  st_nlink;
    HI_S16  st_uid;
    HI_S16  st_gid;
    HI_U32  st_rdev;
    HI_S32  st_size;
    HI_S32  st_atime;    /* time of last access */
    HI_S32  st_mtime;    /* time of last modification */
    HI_S32  st_ctime;    /* time of last status change */
#else
#error YOU MUST DEFINE HI OS TYPE WIN32 OR LINUX !
#endif
} HI_STAT_S;

/*----------------------------------------------*
 * routine prototypes
 *----------------------------------------------*/
/*----------------------------------------------*
 * 目录操作适配接口
 *----------------------------------------------*/

HI_S32 HI_Access( const HI_CHAR *dirname ,HI_S32 mode);

HI_S32 HI_ChDir( const HI_CHAR *dirname );

HI_S32 HI_MkDir( const HI_CHAR *dirname ,HI_MODE_T mode);

//HI_S32 HI_FStat(const HI_S32 fd, HI_STAT_S *buf);

HI_S32 HI_Rename(const HI_CHAR *oldpath, const HI_CHAR *newpath);

/*----------------------------------------------*
 * 文件输入输出接口
 *----------------------------------------------*/

HI_S32 HI_Fprintf (FILE *stream, const HI_CHAR *format, ...);

HI_S32 HI_Fscanf (FILE * stream,const HI_CHAR * format, ...);

HI_S32 HI_Open(const HI_CHAR *pathname, HI_S32 flags, HI_MODE_T mode);

HI_S32 HI_Creat(const HI_CHAR *pathname, HI_MODE_T mode);

HI_SSIZE_T HI_Read(HI_S32 fd, HI_VOID *buf, HI_SIZE_T count);

HI_SSIZE_T HI_Write(HI_S32 fd, const HI_VOID *buf, HI_SIZE_T count);

HI_S32 HI_Close(HI_S32 fd);

HI_S32 HI_CloseHandle(HI_VOID *handle);

HI_OFF_T HI_LSeek(HI_S32 fildes, HI_OFF_T offset, HI_S32 whence);

HI_S32 HI_Ioctl(HI_S32 fd, HI_S32 request,HI_VOID *lpInBuffer,
                HI_U32  nInBufferSize, HI_VOID * lpOutBuffer,
                HI_U32 nOutBufferSize, HI_U32 *lpBytesReturned);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_ADPT_FILE_H__ */
