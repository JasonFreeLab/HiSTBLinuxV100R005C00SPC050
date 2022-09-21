/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_kernel_file.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年9月18日
  最近修改   :
  功能描述   : oal_kernel_file.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月18日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_LINUX_KERNEL_FILE_H__
#define __OAL_LINUX_KERNEL_FILE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/syscalls.h>
#include <asm/unistd.h>
#include <asm/uaccess.h>

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define OAL_KERNEL_DS           KERNEL_DS

/*文件属性*/
#define OAL_O_ACCMODE           O_ACCMODE
#define OAL_O_RDONLY            O_RDONLY
#define OAL_O_WRONLY            O_WRONLY
#define OAL_O_RDWR              O_RDWR
#define OAL_O_CREAT             O_CREAT
#define OAL_O_TRUNC             O_TRUNC
#define OAL_O_APPEND            O_APPEND

#define OAL_PRINT_FORMAT_LENGTH     512                     /* 打印格式字符串的最大长度 */

typedef struct file             oal_file;
typedef mm_segment_t            oal_mm_segment_t;


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


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  10 函数声明
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_mm_segment_t oal_get_fs(oal_void)
{
    return  get_fs();
}

OAL_STATIC OAL_INLINE oal_void oal_set_fs(oal_mm_segment_t fs)
{
    return set_fs(fs);
}

OAL_STATIC OAL_INLINE oal_int oal_kernel_file_close(oal_file *pst_file)
{
    return filp_close(pst_file,NULL);
}
#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
extern oal_kobject* oal_get_sysfs_root_object(oal_void);
extern oal_kobject* oal_get_sysfs_root_boot_object(oal_void);
extern oal_kobject* oal_conn_sysfs_root_obj_init(oal_void);
extern oal_void oal_conn_sysfs_root_obj_exit(oal_void);
extern oal_void oal_conn_sysfs_root_boot_obj_exit(oal_void);
#endif
extern oal_file* oal_kernel_file_open(oal_uint8 *file_path,oal_int32 ul_attribute);
extern loff_t oal_kernel_file_size(oal_file *pst_file);
extern oal_void *oal_kernel_file_read(oal_file *pst_file,loff_t ul_fsize);
extern oal_int oal_kernel_file_write(oal_file *pst_file,oal_uint8 *pst_buf,loff_t fsize);
extern oal_int oal_kernel_file_print(oal_file *pst_file,const oal_int8 *pc_fmt,...);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_main */
