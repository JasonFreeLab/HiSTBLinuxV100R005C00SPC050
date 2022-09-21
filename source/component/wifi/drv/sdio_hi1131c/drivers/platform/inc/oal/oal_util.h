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

#ifndef __OAL_UTIL_H__
#define __OAL_UTIL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "oal_mm.h"
#include "arch/oal_util.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define OAL_VA_START            va_start
#define OAL_VA_END              va_end

#define OAL_VA_LIST             va_list

/* 拼接为16 bit或者 32bit */
#define OAL_MAKE_WORD16(lsb, msb) ((((oal_uint16)(msb) << 8) & 0xFF00) | (lsb))
#define OAL_MAKE_WORD32(lsw, msw) ((((oal_uint32)(msw) << 16) & 0xFFFF0000) | (lsw))


/* 计算为字节对齐后填充后的长度 */
#define OAL_ROUNDUP(_old_len, _align)  ((((_old_len) + ((_align) - 1)) / (_align)) * (_align))

/* increment with wrap-around */
#define OAL_INCR(_l, _sz)   (_l)++; (_l) &= ((_sz) - 1)
#define OAL_DECR(_l, _sz)   (_l)--; (_l) &= ((_sz) - 1)

/* 获取大小 */
#define OAL_SIZEOF                                  sizeof

/* 获取数组大小 */
#define OAL_ARRAY_SIZE(_ast_array)                  (sizeof(_ast_array) / sizeof((_ast_array)[0]))

/* 四字节对齐 */
#define OAL_GET_4BYTE_ALIGN_VALUE(_ul_size)         (((_ul_size) + 0x03) & (~0x03))

/* 获取当前线程信息 */
#define OAL_CURRENT_TASK     (current_thread_info()->task)

#define OAL_SWAP_BYTEORDER_16(_val) ((((_val) & 0x00FF) << 8) + (((_val) & 0xFF00) >> 8))

#if (_PRE_BIG_CPU_ENDIAN == _PRE_CPU_ENDIAN)          /* BIG_ENDIAN */
#define OAL_BYTEORDER_TO_LE32(_val)        OAL_SWAP_BYTEORDER_32(_val)
#define OAL_BYTEORDER_TO_LE16(_val)        OAL_SWAP_BYTEORDER_16(_val)
#define OAL_MASK_INVERSE(_len, _offset)    ((oal_uint32)(OAL_SWAP_BYTEORDER_32(~(((1 << (_len)) - 1) << (_offset)))))
#define OAL_MASK(_len, _offset)            ((oal_uint32)(OAL_SWAP_BYTEORDER_32(((1 << (_len)) - 1) << (_offset))))
#define OAL_NTOH_16(_val)                  (_val)
#define OAL_NTOH_32(_val)                  (_val)
#define OAL_HTON_16(_val)                  (_val)
#define OAL_HTON_32(_val)                  (_val)

#elif (_PRE_LITTLE_CPU_ENDIAN == _PRE_CPU_ENDIAN)     /* LITTLE_ENDIAN */
#define OAL_BYTEORDER_TO_LE32(_val)        (_val)
#define OAL_BYTEORDER_TO_LE16(_val)        (_val)
#define OAL_MASK_INVERSE(_len, _offset)    ((oal_uint32)(~(((1UL << (_len)) - 1) << (_offset))))
#define OAL_MASK(_len, _offset)            ((oal_uint32)(((1UL << (_len)) - 1) << (_offset)))
#define OAL_NTOH_16(_val)                  OAL_SWAP_BYTEORDER_16(_val)
#define OAL_NTOH_32(_val)                  OAL_SWAP_BYTEORDER_32(_val)
#define OAL_HTON_16(_val)                  OAL_SWAP_BYTEORDER_16(_val)
#define OAL_HTON_32(_val)                  OAL_SWAP_BYTEORDER_32(_val)

#endif


#if 0  /* 编不过 */
#ifndef current
#define current (0)
#endif
#endif

/* 比较宏 */
#define OAL_MIN(_A, _B) (((_A) < (_B))? (_A) : (_B))

/* 比较宏 */
#define OAL_MAX(_A, _B) (((_A) > (_B))? (_A) : (_B))

#define OAL_SUB(_A, _B) (((_A) > (_B))? ((_A) - (_B)) : (0))

#define OAL_ABSOLUTE_SUB(_A, _B) (((_A) > (_B))? ((_A) - (_B)) : ((_B) - (_A)))

/* 从某个设备读取某个寄存器地址的32-bit寄存器的值。*/
#define OAL_REG_READ32(_addr)    \
        *((OAL_VOLATILE oal_uint32 *)(_addr))

#define OAL_REG_READ16(_addr)    \
    *((OAL_VOLATILE oal_uint16 *)(_addr))

/* 往某个设备某个32-bit寄存器地址写入某个值 */
#define OAL_REG_WRITE32(_addr, _val)    \
    (*((OAL_VOLATILE oal_uint32 *)(_addr)) = (_val))
#define OAL_REG_WRITE16(_addr, _val)    \
    (*((OAL_VOLATILE oal_uint16 *)(_addr)) = (_val))

/* Is val aligned to "align" ("align" must be power of 2) */
#ifndef IS_ALIGNED
#define OAL_IS_ALIGNED(val, align)		\
	(((oal_uint32)(val) & ((align) - 1)) == 0)
#else
#define OAL_IS_ALIGNED  IS_ALIGNED
#endif


/* Bit Values */
#define BIT31                   ((oal_uint32)(1UL << 31))
#define BIT30                   ((oal_uint32)(1 << 30))
#define BIT29                   ((oal_uint32)(1 << 29))
#define BIT28                   ((oal_uint32)(1 << 28))
#define BIT27                   ((oal_uint32)(1 << 27))
#define BIT26                   ((oal_uint32)(1 << 26))
#define BIT25                   ((oal_uint32)(1 << 25))
#define BIT24                   ((oal_uint32)(1 << 24))
#define BIT23                   ((oal_uint32)(1 << 23))
#define BIT22                   ((oal_uint32)(1 << 22))
#define BIT21                   ((oal_uint32)(1 << 21))
#define BIT20                   ((oal_uint32)(1 << 20))
#define BIT19                   ((oal_uint32)(1 << 19))
#define BIT18                   ((oal_uint32)(1 << 18))
#define BIT17                   ((oal_uint32)(1 << 17))
#define BIT16                   ((oal_uint32)(1 << 16))
#define BIT15                   ((oal_uint32)(1 << 15))
#define BIT14                   ((oal_uint32)(1 << 14))
#define BIT13                   ((oal_uint32)(1 << 13))
#define BIT12                   ((oal_uint32)(1 << 12))
#define BIT11                   ((oal_uint32)(1 << 11))
#define BIT10                   ((oal_uint32)(1 << 10))
#define BIT9                    ((oal_uint32)(1 << 9))
#define BIT8                    ((oal_uint32)(1 << 8))
#define BIT7                    ((oal_uint32)(1 << 7))
#define BIT6                    ((oal_uint32)(1 << 6))
#define BIT5                    ((oal_uint32)(1 << 5))
#define BIT4                    ((oal_uint32)(1 << 4))
#define BIT3                    ((oal_uint32)(1 << 3))
#define BIT2                    ((oal_uint32)(1 << 2))
#define BIT1                    ((oal_uint32)(1 << 1))
#define BIT0                    ((oal_uint32)(1 << 0))
#define ALL                     0xFFFF

#define BIT(nr)                 (1UL << (nr))

#define OAL_BITS_PER_BYTE       8   /* 一个字节中包含的bit数目 */


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
#ifdef _PRE_CONFIG_HISI_PANIC_DUMP_SUPPORT
typedef  struct _hwifi_panic_log_   hwifi_panic_log;
typedef oal_int32 (* hwifi_panic_log_cb)(oal_void* data,oal_uint8*pst_buf,oal_int32 buf_len);
struct _hwifi_panic_log_
{
    struct list_head list;
    /*the log module name*/
    char* name;
    hwifi_panic_log_cb    cb;
    oal_void* data;
};
#define DECLARE_WIFI_PANIC_STRU(module_name,func) \
        hwifi_panic_log module_name = \
        {\
            .name = #module_name,\
            .cb = (hwifi_panic_log_cb)func,\
        }
#endif

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#ifdef _PRE_CONFIG_HISI_PANIC_DUMP_SUPPORT
/*****************************************************************************
 函 数 名  : hwifi_panic_log_register
 功能描述  : Kernl Panic 的回调函数注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
extern oal_void hwifi_panic_log_register(hwifi_panic_log* log, void* data);
extern oal_void hwifi_panic_log_dump(char* print_level);
#else
OAL_STATIC OAL_INLINE oal_void hwifi_panic_log_dump(char* print_level)
{
}
#endif

/*****************************************************************************
 函 数 名  : oal_strtohex
 功能描述  : 将一个字符转化成16进制数
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
OAL_STATIC OAL_INLINE oal_uint8  oal_strtohex(const oal_int8 *c_string)
{
    oal_uint8 uc_ret = 0;

    if (*c_string >= '0' && *c_string <= '9')
    {
        uc_ret = (oal_uint8)(*c_string - '0');
    }
    else if (*c_string >= 'A' && *c_string <= 'F')
    {
        uc_ret = (oal_uint8)(*c_string - 'A' + 10);
    }
    else if (*c_string >= 'a' && *c_string <= 'f')
    {
        uc_ret = (oal_uint8)(*c_string - 'a' + 10);
    }

    return uc_ret;
}

/*****************************************************************************
 函 数 名  : oal_strtoaddr
 功能描述  : 字符串转MAC地址
 输入参数  : pc_param: MAC地址字符串, 格式 xx:xx:xx:xx:xx:xx  分隔符支持':'与'-'
 输出参数  : puc_mac_addr: 转换成16进制后的MAC地址
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_strtoaddr(const oal_int8 *pc_param, oal_uint8 *puc_mac_addr)
{
    oal_uint8   uc_char_index;

    /* 获取mac地址,16进制转换 */
    for (uc_char_index = 0; uc_char_index < 12; uc_char_index++)
    {
        if ((':' == *pc_param) || ('-' == *pc_param))
        {
            pc_param++;
            if (0 != uc_char_index)
            {
                uc_char_index--;
            }

            continue;
        }

        puc_mac_addr[uc_char_index/2] =
        (oal_uint8)(puc_mac_addr[uc_char_index/2] * 16 * (uc_char_index % 2) +
                                        oal_strtohex(pc_param));
        pc_param++;
    }

}


/*****************************************************************************
 函 数 名  : oal_get_random
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_get_random(oal_void)
{
    /* TBD */
    return 1;
}

/*****************************************************************************
 函 数 名  : oal_gen_random
 功能描述  : 产生随机数
 输入参数  : ul_val:随机种子   us_rst_flag:0:不更新随机种子，非0:更新随机种子
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_gen_random(oal_uint32 ul_val, oal_uint8 us_rst_flag)
{
    static oal_uint32 ul_rand = 0;
    if (0 != us_rst_flag)
    {
        ul_rand = ul_val;
    }
    ul_rand = ul_rand * 1664525L + 1013904223L;
	return (oal_uint8) (ul_rand >> 24);
}

/*****************************************************************************
 函 数 名  : oal_bit_get_num_one_byte
 功能描述  : 获取单字节中的bit1的个数
 输入参数  : uc_byte:需要操作的字节
 输出参数  : 无
 返 回 值  : bit的个数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_bit_get_num_one_byte(oal_uint8 uc_byte)
{

    uc_byte = (uc_byte & 0x55) + ((uc_byte >> 1) & 0x55);
    uc_byte = (uc_byte & 0x33) + ((uc_byte >> 2) & 0x33);
    uc_byte = (uc_byte & 0x0F) + ((uc_byte >> 4) & 0x0F);

    return uc_byte;
}

/*****************************************************************************
 函 数 名  : oal_bit_get_num_four_byte
 功能描述  : 获取4字节中bit1的个数
 输入参数  : uc_byte:需要操作的字节
 输出参数  : 无
 返 回 值  : bit的个数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_bit_get_num_four_byte(oal_uint32 ul_byte)
{
    ul_byte = (ul_byte & 0x55555555) + ((ul_byte >>  1) & 0x55555555);
    ul_byte = (ul_byte & 0x33333333) + ((ul_byte >>  2) & 0x33333333);
    ul_byte = (ul_byte & 0x0F0F0F0F) + ((ul_byte >>  4) & 0x0F0F0F0F);
    ul_byte = (ul_byte & 0x00FF00FF) + ((ul_byte >>  8) & 0x00FF00FF);
    ul_byte = (ul_byte & 0x0000FFFF) + ((ul_byte >> 16) & 0x0000FFFF);

    return ul_byte;
}

/*****************************************************************************
 函 数 名  : oal_bit_set_bit_one_byte
 功能描述  : 对1字节的指定位置一
 输入参数  : puc_byte: 要进行位操作的变量地址
             nr: 置位的位数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_bit_set_bit_one_byte(oal_uint8 *puc_byte, oal_bitops nr)
{
    *puc_byte |= ((oal_uint8)(1 << nr));
}

/*****************************************************************************
 函 数 名  : oal_bit_clear_bit_one_byte
 功能描述  : 对1字节的指定位置零
 输入参数  : puc_byte: 要进行位操作的变量地址
             nr: 置零的位数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_bit_clear_bit_one_byte(oal_uint8 *puc_byte, oal_bitops nr)
{
    *puc_byte &=(~((oal_uint8)(1 << nr)));
}

/*****************************************************************************
 函 数 名  : oal_bit_set_bit_four_byte
 功能描述  : 对4字节的指定位置一
 输入参数  : pul_byte: 要进行位操作的变量地址
             nr: 置位的位数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_bit_set_bit_four_byte(oal_uint32 *pul_byte, oal_bitops nr)
{
    *pul_byte |= ((oal_uint32)(1 << nr));
}

/*****************************************************************************
 函 数 名  : oal_bit_clear_bit_four_byte
 功能描述  : 对4字节的指定位置零
 输入参数  : pul_byte: 要进行位操作的变量地址
             nr: 置零的位数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_bit_clear_bit_four_byte(oal_uint32 *pul_byte, oal_bitops nr)
{
    *pul_byte &= ~((oal_uint32)(1 << nr));
}

/*****************************************************************************
 函 数 名  : oal_bit_set_bit_eight_byte
 功能描述  : 对8字节的指定位置一
 输入参数  : oal_uint64 *pull_byte
             oal_bitops nr
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月26日,星期四
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_bit_set_bit_eight_byte(oal_uint64 *pull_byte, oal_bitops nr)
{
    *pull_byte |= ((oal_uint64)1 << nr);
}

/*****************************************************************************
 函 数 名  : oal_bit_clear_bit_eight_byte
 功能描述  : 对8字节的指定位置0
 输入参数  : oal_uint64 *pull_byte
             oal_bitops nr
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月26日,星期四
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_bit_clear_bit_eight_byte(oal_uint64 *pull_byte, oal_bitops nr)
{
    *pull_byte &= ~((oal_uint64)1 << nr);
}

/*****************************************************************************
 函 数 名  : oal_bit_find_first_bit_one_byte
 功能描述  : 找到1字节右数第一个是1的位数
 输入参数  : puc_byte: 要查找的字节
 输出参数  : 无
 返 回 值  : 右数第一个是1的位数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_bit_find_first_bit_one_byte(oal_uint8 uc_byte)
{
    oal_uint8 uc_ret = 0;

    uc_byte = uc_byte & (-uc_byte);

    while (uc_byte != 1)
    {
        uc_ret++;
        uc_byte = (uc_byte >> 1);

        if (uc_ret > 7)
        {
            return uc_ret;
        }
    }

    return uc_ret;
}

/*****************************************************************************
 函 数 名  : oal_bit_find_first_zero_one_byte
 功能描述  : 找到1字节右数第一个是0的位数
 输入参数  : puc_byte: 要查找的字节
 输出参数  : 无
 返 回 值  : 右数第一个是0的位数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_bit_find_first_zero_one_byte(oal_uint8 uc_byte)
{
    oal_uint8 uc_ret = 0;

    uc_byte = ~uc_byte;
    uc_byte = uc_byte & (-uc_byte);

    while (uc_byte != 1)
    {
        uc_ret++;
        uc_byte = (uc_byte >> 1);

        if (uc_ret > 7)
        {
            return uc_ret;
        }
    }

    return uc_ret;
}

/*****************************************************************************
 函 数 名  : oal_bit_find_first_bit_four_byte
 功能描述  : 找到1字节右数第一个是1的位数
 输入参数  : puc_byte: 要查找的字节
 输出参数  : 无
 返 回 值  : 右数第一个是1的位数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_bit_find_first_bit_four_byte(oal_uint32 ul_byte)
{
    oal_uint8 uc_ret = 0;

    if (0 == ul_byte)
    {
        return uc_ret;
    }

    if (!(ul_byte & 0xffff))
    {
        ul_byte >>= 16;
        uc_ret += 16;
    }

    if (!(ul_byte & 0xff))
    {
        ul_byte >>= 8;
        uc_ret += 8;
    }

    if (!(ul_byte & 0xf))
    {
        ul_byte >>= 4;
        uc_ret += 4;
    }

    if (!(ul_byte & 3))
    {
        ul_byte >>= 2;
        uc_ret += 2;
    }

    if (!(ul_byte & 1))
    {
        uc_ret += 1;
    }

    return uc_ret;
}

/*****************************************************************************
 函 数 名  : oal_bit_find_first_zero_four_byte
 功能描述  : 找到1字节右数第一个是0的位数
 输入参数  : puc_byte: 要查找的字节
 输出参数  : 无
 返 回 值  : 右数第一个是0的位数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_bit_find_first_zero_four_byte(oal_uint32 ul_byte)
{
    oal_uint8 uc_ret = 0;

    ul_byte = ~ul_byte;

    if (!(ul_byte & 0xffff))
    {
        ul_byte >>= 16;
        uc_ret += 16;
    }

    if (!(ul_byte & 0xff))
    {
        ul_byte >>= 8;
        uc_ret += 8;
    }

    if (!(ul_byte & 0xf))
    {
        ul_byte >>= 4;
        uc_ret += 4;
    }

    if (!(ul_byte & 3))
    {
        ul_byte >>= 2;
        uc_ret += 2;
    }

    if (!(ul_byte & 1))
    {
        ul_byte >>= 1;
        uc_ret += 1;
    }

    return uc_ret;
}

/*****************************************************************************
 函 数 名  : oal_set_mac_addr
 功能描述  : 将第二个mac地址 赋值给diyimac地址
 输入参数  : puc_mac_addr1: 第一个mac地址
             puc_mac_addr2: 第二个mac地址
 输出参数  : 无
 返 回 值  : 成功OAL_SUCC，失败OAL_ERR_CODE_PTR_NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_set_mac_addr(oal_uint8 *puc_mac_addr1, oal_uint8 *puc_mac_addr2)
{
    puc_mac_addr1[0] = puc_mac_addr2[0];
    puc_mac_addr1[1] = puc_mac_addr2[1];
    puc_mac_addr1[2] = puc_mac_addr2[2];
    puc_mac_addr1[3] = puc_mac_addr2[3];
    puc_mac_addr1[4] = puc_mac_addr2[4];
    puc_mac_addr1[5] = puc_mac_addr2[5];
}

/*****************************************************************************
 函 数 名  : oal_set_mac_addr_zero
 功能描述  : mac地址置零
 输入参数  : puc_mac_addr: 需清零的mac地址的指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_set_mac_addr_zero(oal_uint8 *puc_mac_addr)
{
    puc_mac_addr[0] = 0;
    puc_mac_addr[1] = 0;
    puc_mac_addr[2] = 0;
    puc_mac_addr[3] = 0;
    puc_mac_addr[4] = 0;
    puc_mac_addr[5] = 0;
}

/*****************************************************************************
 函 数 名  : oal_compare_mac_addr
 功能描述  : 比较两个mac地址是否相等
 输入参数  : puc_mac_addr1: 第一个mac地址
             puc_mac_addr2: 第二个mac地址
 输出参数  : 无
 返 回 值  : 不等返回1 ； 相等返回0
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_compare_mac_addr(oal_uint8 *puc_mac_addr1, oal_uint8 *puc_mac_addr2)

{
    return (puc_mac_addr1[0] ^ puc_mac_addr2[0]) | (puc_mac_addr1[1] ^ puc_mac_addr2[1])
    | (puc_mac_addr1[2] ^ puc_mac_addr2[2]) | (puc_mac_addr1[3] ^ puc_mac_addr2[3])
    | (puc_mac_addr1[4] ^ puc_mac_addr2[4]) | (puc_mac_addr1[5] ^ puc_mac_addr2[5]);
}

/*****************************************************************************
 函 数 名  : oal_set_ip_addr
 功能描述  : 将第二个ip地址 赋值给第一个ip地址
 输入参数  : puc_ip_addr1: 第一个mac地址
             puc_ip_addr2: 第二个mac地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_set_ip_addr(oal_uint8 *puc_ip_addr1, oal_uint8 *puc_ip_addr2)
{
    puc_ip_addr1[0] = puc_ip_addr2[0];
    puc_ip_addr1[1] = puc_ip_addr2[1];
    puc_ip_addr1[2] = puc_ip_addr2[2];
    puc_ip_addr1[3] = puc_ip_addr2[3];
}

/*****************************************************************************
 函 数 名  : oal_cmp_seq_num
 功能描述  : 比较两个接收描述符的中断顺序号的大小，seq_num1大于seq_num2返回真
 输入参数  : (1)数值1
             (2)数值2
             (3)两个数值间的最大差值
 输出参数  : 无
 返 回 值  : OAL_TRUE或者OAL_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  oal_cmp_seq_num(
                oal_uint32   ul_seq_num1,
                oal_uint32   ul_seq_num2,
                oal_uint32   ul_diff_value)
{
    if (((ul_seq_num1 < ul_seq_num2) && ((ul_seq_num2 - ul_seq_num1) < ul_diff_value))
       ||((ul_seq_num1 > ul_seq_num2) && ((ul_seq_num1- ul_seq_num2) > ul_diff_value)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : oal_strcmp
 功能描述  : 字符串比较
 输入参数  : pc_src: 源字符串
             pc_dst: 目的字符串
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32 oal_strcmp(const oal_int8 *pc_src, const oal_int8 *pc_dst)
{
    oal_int8  c_c1;
    oal_int8  c_c2;
    oal_int32 l_ret = 0;

    do
    {
        c_c1 = *pc_src++;
        c_c2 = *pc_dst++;
        l_ret = c_c1 - c_c2;
        if (l_ret)
        {
            break;
        }
    }while (c_c1);

    return l_ret;
}

/*****************************************************************************
 函 数 名  : oal_strim
 功能描述  : 去掉字符串开始与结尾的空格
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int8 *oal_strim(oal_int8 *pc_s)
{
    oal_uint32 ul_size;
    oal_int8  *pc_end;

    while (' ' == *pc_s)
    {
        ++pc_s;
    }

    ul_size = OAL_STRLEN(pc_s);
    if (!ul_size)
    {
        return pc_s;
    }

    pc_end = pc_s + ul_size - 1;
    while (pc_end >= pc_s && ' ' == *pc_end)
    {
        pc_end--;
    }

    *(pc_end + 1) = '\0';

    return pc_s;
}

/*****************************************************************************
 函 数 名  : oal_strcat
 功能描述  : 往dest字符串后追加src字符串
 输入参数  : oal_int8 *dest
             const oal_int8 *src
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_int8  *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月6日,星期四
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int8  *oal_strcat(oal_int8 *dest, const oal_int8 *src)
{
    oal_int8   *pc_tmp;

    pc_tmp = dest;

    while (*dest)
    {
        dest++;
    }

    while ((*dest++ = *src++) != '\0')
    {
        ; //do nothing
    }

    return pc_tmp;
}

/*****************************************************************************
 函 数 名  : oal_strncat
 功能描述  : 往dest字符串从src中添加指定个数字符
 输入参数  : oal_int8 *dest
             const oal_int8 *src
             oal_int32 l_cnt
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_int8  *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月6日,星期四
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int8  *oal_strncat(oal_int8 *dest, const oal_int8 *src, oal_int32 l_cnt)
{
    oal_int8   *pc_tmp;

    pc_tmp = dest;

    if (l_cnt <= 0)
    {
        return pc_tmp;
    }

    while (*dest)
    {
        dest++;
    }

    while ((*dest++ = *src++) != '\0')
    {
        if (--l_cnt == 0)
        {
            *dest = '\0';
            break;
        }
    }

    return pc_tmp;
}

/*****************************************************************************
 函 数 名  : oal_strstr
 功能描述  : 在pc_s1中查找pc_s2第一次出现的位置
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
OAL_STATIC OAL_INLINE oal_int8*  oal_strstr(oal_int8 *pc_s1, oal_int8 *pc_s2)
{
    return OAL_STRSTR(pc_s1, pc_s2);
}


/*****************************************************************************
 函 数 名  : oal_init_lut
 功能描述  : 初始化传入的LUT BITMAP表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_init_lut(oal_uint8  *puc_lut_index_table, oal_uint8 uc_bmap_len)
{
    oal_uint8   uc_lut_idx;

    for (uc_lut_idx = 0; uc_lut_idx < uc_bmap_len; uc_lut_idx++)
    {
        puc_lut_index_table[uc_lut_idx] = 0;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_get_lut_index
 功能描述  : 从LUT index bitmap表中，获取一个没有被使用的索引，没有找到的话，
             返回不可用的索引标识(非关键路径，未进行优化，有时间可以优化)
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_get_lut_index(
                oal_uint8      *puc_lut_index_table,
                oal_uint8       uc_bmap_len,
                oal_uint16      us_max_lut_size)
{
    oal_uint8       uc_byte     = 0;
    oal_uint8       uc_bit      = 0;
    oal_uint8       uc_temp     = 0;
    oal_uint16      us_index    = 0;

    for (uc_byte = 0; uc_byte < uc_bmap_len; uc_byte++)
    {
        uc_temp = puc_lut_index_table[uc_byte];

        for (uc_bit = 0; uc_bit < 8; uc_bit++)
        {
            if (0x0 == (uc_temp & (1 << uc_bit)))
            {
                us_index = (uc_byte * 8 + uc_bit);

                if (us_index < us_max_lut_size)
                {
                    puc_lut_index_table[uc_byte] |= (oal_uint8)(1 << uc_bit);

                    return (oal_uint8)us_index;
                }
                else
                {
                    return (oal_uint8)us_max_lut_size;
                }
            }
        }
    }

    return (oal_uint8)us_max_lut_size;
}

/*****************************************************************************
 函 数 名  : oal_del_lut_index
 功能描述  : 在LUT index bitmap表中，删除一个LUT index (注:%可以作为优化项)
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_del_lut_index(oal_uint8 *puc_lut_index_table, oal_uint8 uc_idx)
{
    oal_uint8 uc_byte = uc_idx / 8;
    oal_uint8 uc_bit  = uc_idx % 8;

    puc_lut_index_table[uc_byte] &= ~(oal_uint8)(1 << uc_bit);
}

/*****************************************************************************
 函 数 名  : oal_get_virt_addr
 功能描述  : 物理地址转化为虚拟地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32* oal_get_virt_addr(oal_uint32 *pul_phy_addr)
{
    /* 空指针无需转化 */
    if (OAL_PTR_NULL == pul_phy_addr)
    {
        return pul_phy_addr;
    }

    return (oal_uint32 *)OAL_PHY_TO_VIRT_ADDR((oal_uint)pul_phy_addr);
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_util.h */
