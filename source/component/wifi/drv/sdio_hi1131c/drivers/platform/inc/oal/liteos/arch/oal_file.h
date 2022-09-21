/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_file.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年07月29日
  最近修改   :
  功能描述   : oal_file.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年07月29日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_LITEOS_FILE_H__
#define __OAL_LITEOS_FILE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include <linux/fs.h>
#include <fs/fs.h>
#include <fcntl.h>
#include "oal_mm.h"
#include <oal_types.h>

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*文件属性*/
#define OAL_O_ACCMODE           O_ACCMODE
#define OAL_O_RDONLY            O_RDONLY
#define OAL_O_WRONLY            O_WRONLY
#define OAL_O_RDWR              O_RDWR
#define OAL_O_CREAT             O_CREAT
#define OAL_O_TRUNC             O_TRUNC
#define OAL_O_APPEND            O_APPEND
#define OAL_O_EXCL              O_EXCL  /* not fcntl */
#define OAL_O_NOCTTY            O_NOCTTY    /* not fcntl */
#define OAL_O_NOCTTY            O_NONBLOCK  
#define OAL_O_DSYNC             O_DSYNC          /* used to be O_SYNC, see below */
#define OAL_FASYNC              FASYNC            /* fcntl, for BSD compatibility */
#define OAL_O_DIRECT            O_DIRECT        /* direct disk access hint */
#define OAL_O_LARGEFILE         O_LARGEFILE  
#define OAL_O_DIRECTORY         O_DIRECTORY      /* must be a directory */
#define OAL_O_NOFOLLOW          O_NOFOLLOW        /* don't follow links */
#define OAL_O_NOATIME           O_NOATIME  
#define OAL_O_CLOEXEC           O_CLOEXEC      /* set close_on_exec */


#define OAL_SEEK_SET      SEEK_SET     /* Seek from beginning of file.  */
#define OAL_SEEK_CUR     SEEK_CUR    /* Seek from current position.  */
#define OAL_SEEK_END     SEEK_END    /* Set file pointer to EOF plus "offset" */

#define OAL_FILE_POS(pst_file)      oal_get_file_pos(pst_file)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

typedef struct _oal_file_stru_{
    int fd;
}oal_file_stru;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : oal_file_open
 功能描述  : 打开文件
 输入参数  : pc_path: 文件路径，flags:打开方式,rights:打开权限
 输出参数  : 无
 返 回 值  : 文件句柄
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_file_stru* oal_file_open(const oal_int8 *pc_path,oal_int32 flags,oal_int32 rights)
{
    oal_file_stru   *pst_file = NULL;
    pst_file = calloc(1, sizeof(oal_file_stru));
    if (pst_file == NULL)
        return NULL;
    pst_file->fd = open(pc_path, flags, rights);
    if (pst_file->fd < 0)
    {
        free(pst_file);
        return NULL;
    }
    return pst_file;
}

/*****************************************************************************
 函 数 名  : oal_file_write
 功能描述  : 写文件
 输入参数  : file: 文件句柄
           : pc_string: 输入内容地址
           : ul_length: 输入内容长度
 输出参数  : 无
 返 回 值  : 文件句柄
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 oal_file_write(oal_file_stru *pst_file, oal_int8 *pc_string, oal_uint32 ul_length)
{
    return write(pst_file->fd,pc_string,ul_length);
}

/*****************************************************************************
 函 数 名  : oal_file_close
 功能描述  : 关闭文件
 输入参数  : pc_path: 文件路径
 输出参数  : 无
 返 回 值  : 文件句柄
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_file_close(oal_file_stru *pst_file)
{
    close(pst_file->fd);
    free(pst_file);
    pst_file= NULL;
}

/*****************************************************************************
 函 数 名  : oal_file_read
 功能描述  : 内核读文件，从头开始读
 输入参数  : file:指向要读取的文件的指针
             puc_buf:从文件读出数据后存放的buf
             ul_count:指定要读取的长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_file_read(oal_file_stru *pst_file,
                                                 oal_int8 *pc_buf,
                                                 oal_uint32 ul_count)
{
    return read(pst_file->fd, pc_buf, ul_count);
}

OAL_STATIC OAL_INLINE oal_int64  oal_file_lseek(oal_file_stru *pst_file,oal_int64 offset,oal_int32 whence)
{
    return lseek(pst_file->fd, offset, whence);
}

/*****************************************************************************
 函 数 名  : oal_file_size
 功能描述  : 获取文件大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_file_size(const oal_int8 *pc_path, oal_uint32   *pul_file_size)
{
    oal_file_stru     *p_file;

    p_file = oal_file_open(pc_path,(OAL_O_RDONLY),0);
    if (OAL_PTR_NULL == p_file)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    *pul_file_size = oal_file_lseek(p_file,0,OAL_SEEK_END);
    oal_file_close(p_file);

    return OAL_SUCC;
}


OAL_STATIC OAL_INLINE oal_int32  oal_get_file_pos(oal_file_stru *pst_file)
{
    struct file *fp = NULL;
    fp = fs_getfilep(pst_file->fd);
    return (int)fp->f_pos;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_file.h */
