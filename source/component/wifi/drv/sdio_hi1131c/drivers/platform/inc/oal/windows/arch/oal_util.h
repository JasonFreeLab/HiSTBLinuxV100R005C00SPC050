/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_util.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年9月25日
  最近修改   :
  功能描述   : oal_util_linux.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月25日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_WINDOWS_UTIL_H__
#define __OAL_WINDOWS_UTIL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "hsimu_reg.h"
#include <sys/stat.h>
#include "oal_mm.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 32字节序大小端转换 */
#define OAL_SWAP_BYTEORDER_32(_val)        \
        ((((_val) & 0x000000FF) << 24) +     \
        (((_val) & 0x0000FF00) << 8) +       \
        (((_val) & 0x00FF0000) >> 8) +       \
        (((_val) & 0xFF000000) >> 24))

#define L1_CACHE_BYTES		(1 << 5)
#define SMP_CACHE_BYTES L1_CACHE_BYTES

#define SKB_DATA_ALIGN(X)	(((X) + (SMP_CACHE_BYTES - 1)) & \
				 ~(SMP_CACHE_BYTES - 1))


#define OAL_CONST                                   const
/* 获取CORE ID */
#define OAL_GET_CORE_ID()     (g_cpuid_register[0])

typedef LONG                    oal_bitops;

typedef FILE                    oal_file_stru;

typedef struct _stat            oal_file_stat_stru;

#define OAL_FILE_FAIL           OAL_PTR_NULL

#define OAL_LIKELY(_expr)       (_expr)
#define OAL_UNLIKELY(_expr)     (_expr)

#if defined(_PRE_PC_LINT)
#define OAL_FUNC_NAME           "pc_lint"
#else
#define OAL_FUNC_NAME           __FUNCTION__
#endif
#define OAL_RET_ADDR             OAL_PTR_NULL


/* 将几个字符串按照指定格式合成一个字符串 */
#define OAL_SPRINTF             sprintf_s

/* 内存读屏障 */
#define OAL_RMB()

/* 内存写屏障 */
#define OAL_WMB()

/* 内存屏障 */
#define OAL_MB()

#define OAL_OFFSET_OF(TYPE,MEMBER)  ((unsigned long) &((TYPE *)0)->MEMBER)

#define __OAL_DECLARE_PACKED

#define OAL_IO_PRINT            printf

#define OAL_BUG_ON(_con)

#define OAL_WARN_ON(condition)  (condition)

#define OAL_VSPRINTF            vsprintf_s

/* 虚拟地址转物理地址 */
#define OAL_VIRT_TO_PHY_ADDR(_virt_addr)            ((oal_uint32)(_virt_addr))

/* 物理地址转虚拟地址 */
#define OAL_PHY_TO_VIRT_ADDR(_phy_addr)             ((oal_uint32 *)(_phy_addr))

#ifndef current
#define current (0)
#endif

#define OAL_STRLEN                                  strlen
#define OAL_MEMCMP                                  memcmp
#define OAL_STRSTR                                  strstr
#define OAL_STRCMP                                  strcmp


#define OAL_O_ACCMODE           (0)
#define OAL_O_RDONLY             (0)
#define OAL_O_WRONLY            (0)
#define OAL_O_RDWR                (0)
#define OAL_O_CREAT                (0)
#define OAL_O_TRUNC               (0)
#define OAL_O_APPEND              (0)

#define OAL_SEEK_SET      SEEK_SET     /* Seek from beginning of file.  */
#define OAL_SEEK_CUR     SEEK_CUR    /* Seek from current position.  */
#define OAL_SEEK_END     SEEK_END    /* Set file pointer to EOF plus "offset" */

#define OAL_FILE_POS(pst_file)      (0)

#define oal_atomic_inc_return(a)    (0)
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
typedef struct object{
    char* name;
}oal_kobject;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
#define OAL_ROUND_UP(x,y)   OAL_ROUNDUP(x,y)
#define OAL_ROUND_DOWN(value,boundary)  ((value) & (~((boundary)-1)))


/*****************************************************************************
  10 函数声明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : oal_bit_atomic_test_and_set
 功能描述  : 对某个位进行置1操作，并返回该位置的旧值。
 输入参数  : nr: 需要设置的位
             p_addr需要置位的变量地址
 输出参数  :
 返 回 值  : 返回原来bit位的值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_bitops  oal_bit_atomic_test_and_set(oal_bitops nr, OAL_VOLATILE oal_bitops *p_addr)
{
    return InterlockedBitTestAndSet(p_addr, nr);
}

/*****************************************************************************
 函 数 名  : oal_bit_atomic_clear
 功能描述  : 封装各个操作系统平台下对某个位进行清0操作。
 输入参数  : nr: 需要清零的位
             p_addr需要清零的变量地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_bit_atomic_clear(oal_bitops nr, OAL_VOLATILE oal_bitops *p_addr)
{
    InterlockedBitTestAndReset(p_addr, nr);
}

/*****************************************************************************
 函 数 名  : oal_byteorder_host_to_net_uint16
 功能描述  : 将16位本地字节序转换为网络字节序
 输入参数  : us_byte: 需要字节序转换的变量
 输出参数  : 无
 返 回 值  : 转换好的变量
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_uint16  oal_byteorder_host_to_net_uint16(oal_uint16 us_byte)
{
    us_byte = ((us_byte & 0x00FF) << 8) + ((us_byte & 0xFF00) >> 8);

    return us_byte;
}

/*****************************************************************************
 函 数 名  : oal_byteorder_host_to_net_uint16
 功能描述  : 将16位本地字节序转换为网络字节序
 输入参数  : us_byte: 需要字节序转换的变量
 输出参数  : 无
 返 回 值  : 转换好的变量
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_uint16  oal_byteorder_net_to_host_uint16(oal_uint16 us_byte)
{
    us_byte = ((us_byte & 0x00FF) << 8) + ((us_byte & 0xFF00) >> 8);

    return us_byte;
}

/*****************************************************************************
 函 数 名  : oal_byteorder_host_to_net_uint16
 功能描述  : 将32位本地字节序转换为网络字节序
 输入参数  : us_byte: 需要字节序转换的变量
 输出参数  : 无
 返 回 值  : 转换好的变量
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_byteorder_host_to_net_uint32(oal_uint32 ul_byte)
{
    ul_byte = OAL_SWAP_BYTEORDER_32(ul_byte);

    return ul_byte;
}

/*****************************************************************************
 函 数 名  : oal_byteorder_host_to_net_uint16
 功能描述  : 将32位本地字节序转换为网络字节序
 输入参数  : us_byte: 需要字节序转换的变量
 输出参数  : 无
 返 回 值  : 转换好的变量
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_byteorder_net_to_host_uint32(oal_uint32 ul_byte)
{
    ul_byte = OAL_SWAP_BYTEORDER_32(ul_byte);

    return ul_byte;
}

OAL_INLINE oal_file_stru* oal_file_open(const oal_int8 *pc_path, oal_int32 flags, oal_int32 rights)
{
    oal_file_stru *rlt;

    fopen_s(&rlt, pc_path, "w+");

    if (OAL_PTR_NULL == rlt)
    {
        return OAL_FILE_FAIL;
    }

    return rlt;
}

/*****************************************************************************
 函 数 名  : oal_file_open_rw
 功能描述  : 以读写方式打开指定文件，没有则创建
 输入参数  :
 输出参数  : 无
 返 回 值  : 成功返回打开的文件，失败返回FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_file_stru* oal_file_open_rw(const oal_int8 *pc_path)
{
    oal_file_stru *rlt;

    fopen_s(&rlt, pc_path, "w+");

    if (OAL_PTR_NULL == rlt)
    {
        return OAL_FILE_FAIL;
    }

    return rlt;
}

/*****************************************************************************
 函 数 名  : oal_file_open_append
 功能描述  : 以在尾部加入方式打开指定文件没有则创建
 输入参数  :
 输出参数  : 无
 返 回 值  : 成功返回打开的文件，失败返回FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_file_stru* oal_file_open_append(const oal_int8 *pc_path)
{
    oal_file_stru *rlt;

    fopen_s(&rlt, pc_path, "a");

    if (OAL_PTR_NULL == rlt)
    {
        return OAL_FILE_FAIL;
    }

    return rlt;
}

/*****************************************************************************
 函 数 名  : oal_file_open_readonly
 功能描述  : 已只读方式打开指定文件，注意确定文件一定存在。
 输入参数  :
 输出参数  : 无
 返 回 值  : 成功返回打开的文件，失败返回FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_file_stru* oal_file_open_readonly(const oal_int8 *pc_path)
{
    oal_file_stru* rlt;

    fopen_s(&rlt, pc_path, "r");

    if (OAL_PTR_NULL == rlt)
    {
        return OAL_FILE_FAIL;
    }

    return rlt;
}

/*****************************************************************************
 函 数 名  : oal_file_write
 功能描述  : 写文件
 输入参数  : file:需要进行写操作的文件
             pc_string: 要写进文件字符串的地址
             ul_length: 字符串大小
 输出参数  :
 返 回 值  : 成功返回文件，失败返回FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_file_stru* oal_file_write(oal_file_stru* file, oal_int8 *pc_string, oal_uint32 ul_length)
{
    oal_int32 l_rlt;

    l_rlt = fprintf(file, "%s", pc_string);

    if (l_rlt < 0)
    {
        return OAL_FILE_FAIL;
    }

    return file;
}

/*****************************************************************************
 函 数 名  : oal_file_close
 功能描述  : 关闭指定的文件
 输入参数  : file: 需要关闭的文件
 输出参数  : 无
 返 回 值  : 成功返回0，失败返回-1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_int32 oal_file_close(oal_file_stru* file)
{
    oal_int32 l_rlt;

    l_rlt = fclose(file);

    if (EOF == l_rlt)
    {
        return -1;
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : oal_file_read
 功能描述  : 读取不超过ul_count-1个字符到buf中，读入最后一个字符串，在buf最后加上
             '\0'
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_file_read(oal_file_stru *file,
		                                         oal_int8 *puc_buf,
		                                         oal_uint32 ul_count)
{
    return (oal_int32)fread(puc_buf, 1, ul_count, file);
}


/*****************************************************************************
 函 数 名  : oal_file_close
 功能描述  : 计算文件大小
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_int32  oal_file_size(const oal_int8 *pc_path, oal_uint32 *pul_file_size)
{
    oal_file_stat_stru       st_file_stat;
    oal_int32                l_ret;

    l_ret = _stat(pc_path, &st_file_stat);
    if (OAL_SUCC != l_ret)
    {
        return l_ret;
    }

    *pul_file_size = (oal_uint32)st_file_stat.st_size;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_atoi
 功能描述  : 字符串类型转换成整形
 输入参数  : c_string: 字符串地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_int32  oal_atoi(const oal_int8 *c_string)
{
    return atoi(c_string);
}

/*****************************************************************************
 函 数 名  : oal_itoa
 功能描述  : 整形转字符串
 输入参数  : oal_int32 l_val
             oal_int8 *c_string
             oal_uint8 uc_strlen
 输出参数  : 无
 返 回 值  : OAL_INLINE oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月28日,星期六
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_itoa(oal_int32 l_val, oal_int8 *c_string, oal_uint8 uc_strlen)
{
    _itoa_s(l_val, c_string, uc_strlen, 10);   /* 将字符串转成10进制整形 */
}

/*****************************************************************************
 函 数 名  : oal_strtok
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :,
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int8 *oal_strtok(oal_int8 *pc_token, OAL_CONST oal_int8 *pc_delemit, oal_int8 **ppc_context)
{
    return strtok_s(pc_token, pc_delemit, ppc_context);
}

/*****************************************************************************
 函 数 名  : oal_strtol
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int  oal_strtol(OAL_CONST oal_int8 *pc_nptr, oal_int8 **ppc_endptr, oal_int32 l_base)
{
    return strtol(pc_nptr, ppc_endptr, l_base);
}

/*****************************************************************************
 函 数 名  : oal_udelay
 功能描述  : 微秒级延迟函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_udelay(oal_uint u_loops)
{
}

/*****************************************************************************
 函 数 名  : oal_mdelay
 功能描述  : 毫秒级延迟函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_mdelay(oal_uint u_loops)
{
}

/*****************************************************************************
 函 数 名  : oal_kallsyms_lookup_name
 功能描述  : 根据全局变量名字查找全局变量地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_kallsyms_lookup_name(OAL_CONST oal_uint8 *uc_var_name)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : oal_dump_stack
 功能描述  : 打印函数调用栈
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_dump_stack(oal_void)
{
    /* win32下, do nothing */
}

/*****************************************************************************
 函 数 名  : oal_msleep
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_msleep(oal_uint32 ul_usecs)
{

}

/*****************************************************************************
 函 数 名  : oal_strcpy
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE errno_t oal_strcpy(oal_int8 *pc_dest, OAL_CONST oal_int8 *pc_src)
{
    return strcpy_s((oal_int8 *)pc_dest, strlen(pc_src), pc_src);
}

OAL_STATIC OAL_INLINE oal_void oal_random_ether_addr(oal_uint8 *addr)
{
   addr[0] = 0x22;
   addr[1] = 0x22;
   addr[2] = 0x21;
   addr[3] = 0x22;
   addr[4] = 0x23;
   addr[5] = 0x22;
}

OAL_STATIC OAL_INLINE oal_void oal_print_hex_dump(oal_uint8*addr, oal_int32 len, oal_int32 groupsize,oal_int8* pre_str)
{
    OAL_REFERENCE(groupsize);
    OAL_REFERENCE(addr);
    OAL_REFERENCE(len);
    OAL_REFERENCE(pre_str);
}


OAL_STATIC OAL_INLINE oal_uint32 oal_time_before_eq(oal_uint32 ul_time_a, oal_uint32 ul_time_b)
{
    return OAL_TRUE;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_util.h */
