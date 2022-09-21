/******************************************************************************
 *
 *             Copyright 2009 - 2009, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 *
 ******************************************************************************
 * File Name     : hi_adp_interface.h
 * Description   : OS适配公共头文件
 *
 * History       :
 * Version     Date        Author      DefectNum    Modification:
 * 1.1         2009-2-27   q63946      NULL         Created file
 *
 ******************************************************************************/

#ifndef __HI_ADPT_INTERFACE_H__
#define __HI_ADPT_INTERFACE_H__

#include "hi_type.h"
#include <stdarg.h>
#include <errno.h>
#include <string.h>
//#include "hi_adp_thread.h"
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------*
 * macros
 *----------------------------------------------*/

#define HI_VA_LIST va_list
#define HI_VA_START(argList, arg1) va_start( argList, arg1)
#define HI_VA_END(argList) va_end(argList)
#define HI_VA_ARG(argList,type) va_arg(argList,type)
//typedef HI_U32 HI_Pthread_T;

#if 0
/* Protection bits.  */

#define S_IRUSR __S_IREAD       /* Read by owner.  */
#define S_IWUSR __S_IWRITE      /* Write by owner.  */
#define S_IXUSR __S_IEXEC       /* Execute by owner.  */
/* Read, write, and execute by owner.  */
#define S_IRWXU (__S_IREAD|__S_IWRITE|__S_IEXEC)

# define S_IREAD        S_IRUSR
# define S_IWRITE       S_IWUSR
# define S_IEXEC        S_IXUSR

#define S_IRGRP (S_IRUSR >> 3)  /* Read by group.  */
#define S_IWGRP (S_IWUSR >> 3)  /* Write by group.  */
#define S_IXGRP (S_IXUSR >> 3)  /* Execute by group.  */
/* Read, write, and execute by group.  */
#define S_IRWXG (S_IRWXU >> 3)

#define S_IROTH (S_IRGRP >> 3)  /* Read by others.  */
#define S_IWOTH (S_IWGRP >> 3)  /* Write by others.  */
#define S_IXOTH (S_IXGRP >> 3)  /* Execute by others.  */
/* Read, write, and execute by others.  */
#define S_IRWXO (S_IRWXG >> 3)
#endif

/*mode ,for open file or other*/
#define HI_S_IREAD      0000400         /* read permission, owner */
#define HI_S_IWRITE     0000200         /* write permission, owner */
#define HI_S_IEXEC      0000100         /* execute/search permission, owner */
#define HI_S_IRWXU      (HI_S_IREAD|HI_S_IWRITE|HI_S_IEXEC)
#define HI_S_IRWXG      0000070

/*===============  MMap port define =============================*/

#if HI_OS_TYPE == HI_OS_LINUX

#define  HI_PROT_READ   0x1     /* Page can be read.  */
#define  HI_PROT_WRITE  0x2     /* Page can be written.  */
#define  HI_PROT_EXEC   0x4     /* Page can be executed.  */
#define  HI_PROT_NONE   0x0     /* Page can not be accessed.  */

#elif HI_OS_TYPE == HI_OS_WIN32
#define HI_PAGE_NOACCESS          0x01
#define HI_PAGE_READONLY          0x02
#define HI_PAGE_READWRITE         0x04
#define HI_PAGE_EXECUTE           0x10
/*
#define HI_PAGE_EXECUTE_READ      0x20
#define HI_PAGE_EXECUTE_READWRITE 0x40
#define HI_PAGE_EXECUTE_WRITECOPY 0x80
#define HI_PAGE_GUARD            0x100
#define HI_PAGE_NOCACHE          0x200
#define HI_PAGE_WRITECOMBINE     0x400
*/
#define  HI_PROT_READ     HI_PAGE_READONLY      /* Page can be read.  */
#define  HI_PROT_WRITE   HI_PAGE_READWRITE      /* Page can be written.  */
#define  HI_PROT_EXEC     HI_PAGE_EXECUTE       /* Page can be executed.  */
#define HI_PROT_NONE  HI_PAGE_NOACCESS
#else
#error YOU MUST DEFINE OS TYPE HI_OS_TYPE=HI_OS_WIN32 OR HI_OS_LINUX !
#endif

#define HI_MAP_FAILED -1

/*----------------------------------------------*
 * types
 *----------------------------------------------*/

typedef HI_S32   HI_TIME_T;
//typedef HI_U32 HI_SIZE_T;
typedef HI_U32 HI_MODE_T;

typedef HI_S32   HI_SSIZE_T;
typedef HI_S32   HI_OFF_T;

typedef HI_U32 HI_UID_T;
typedef HI_U32 HI_GID_T;

typedef HI_U32 HI_MSGQNUM_T;
typedef HI_U32 HI_MSGLEN_T;

typedef HI_S32 HI_IntPtr_T;
typedef HI_U32 HI_SockLen_T;

typedef HI_S32 HI_PID_T;

typedef HI_U32 HI_InAddr_T;

#if HI_OS_TYPE == HI_OS_WIN32
typedef HI_CHAR * HI_SemKey_T;
#elif HI_OS_TYPE == HI_OS_LINUX

typedef HI_S32 HI_SemKey_T;
#else
#error YOU MUST DEFINE HI OS TYPE WIN32 OR LINUX !
#endif

typedef struct HI_ipc_perm
{
    HI_SemKey_T key;    /* Key.  */
    HI_UID_T uid;       /* Owner's user ID.  */
    HI_GID_T gid;       /* Owner's group ID.  */
    HI_UID_T cuid;      /* Creator's user ID.  */
    HI_GID_T cgid;      /* Creator's group ID.  */
    HI_U16 mode;        /* Read/write permission.  */
    HI_U16 pad1;
    HI_U16 seq;         /* Sequence number.  */
    HI_U16 pad2;
    HI_U32 unused1;
    HI_U32 unused2;
}HI_IPCPerm_S;

typedef  struct hi_msgbuf {
    HI_S32 mtype;       /* message type, must be > 0 */
    HI_CHAR mtext[1];   /* message data */
}HI_MsgBuf_S;

typedef struct hi_msqid_ds
{
  HI_IPCPerm_S msg_perm;    /* structure describing operation permission */
  HI_TIME_T msg_stime;      /* time of last msgsnd command */
  HI_U32 unused1;
  HI_TIME_T msg_rtime;      /* time of last msgrcv command */
  HI_U32 unused2;
  HI_TIME_T msg_ctime;      /* time of last change */
  HI_U32 unused3;
  HI_U32 msg_cbytes;        /* current number of bytes on queue */
  HI_MSGQNUM_T msg_qnum;    /* number of messages currently on queue */
  HI_MSGLEN_T msg_qbytes;   /* max number of bytes allowed on queue */
  HI_PID_T msg_lspid;       /* pid of last msgsnd() */
  HI_PID_T msg_lrpid;       /* pid of last msgrcv() */
  HI_U32 unused4;
  HI_U32 unused5;
} HI_MsgIDDS_S;

#ifndef HI_BYTE_ORDER
//1234 means little endian
#define    HI_BYTE_ORDER          1234
#endif

#ifdef HI_BYTE_ORDER
//4321 means big endian
#if HI_BYTE_ORDER==4321
#define HI_NTOHL(x) (x)
#define HI_HTONL(x) (x)
#define HI_NTOHS(x) (x)
#define HI_HTONS(x) (x)
#else
#define HI_NTOHL(x) ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define HI_HTONL(x) ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define HI_NTOHS(x) ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#define HI_HTONS(x) ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#endif  /* HI_BYTE_ORDER==HI_BIG_ENDIAN */

#else
#error "Byte order macro (HI_BYTE_ORDER) not defined!"
#endif  /* HI_BYTE_ORDER */

/*----------------------------------------------*
 * routines
 *----------------------------------------------*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_ADPT_INTERFACE_H__ */
