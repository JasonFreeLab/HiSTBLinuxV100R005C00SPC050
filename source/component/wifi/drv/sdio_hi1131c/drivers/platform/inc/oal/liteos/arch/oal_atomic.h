/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_atomic.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年07月29日
  最近修改   :
  功能描述   : oal_atomic.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年07月29日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_LITEOS_ATOMIC_H__
#define __OAL_LITEOS_ATOMIC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

/*****************************************************************************
  2 STRUCT定义
*****************************************************************************/

typedef struct {
    volatile int counter;
} oal_atomic;

typedef oal_ulong    oal_bitops;

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
  7 宏定义
*****************************************************************************/
#define BITS_PER_LONG       32
#define BIT_MASK(nr)        (1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)        ((nr) / BITS_PER_LONG)
#define BITOP_WORD(nr)      ((nr) / BITS_PER_LONG)

#define OAL_ATOMIC_INIT(i)  { (i) }
#define oal_atomic_read(v)  ((v)->counter)
#define oal_atomic_set(v,i) (((v)->counter) = (i))

#define oal_atomic_inc(v)       oal_atomic_add(1, v)
#define oal_atomic_dec(v)       oal_atomic_sub(1, v)

#define oal_atomic_inc_and_test(v)  (oal_atomic_add_return(1, v) == 0)
#define oal_atomic_dec_and_test(v)  (oal_atomic_sub_return(1, v) == 0)
#define oal_atomic_inc_return(v)    (oal_atomic_add_return(1, v))
#define oal_atomic_dec_return(v)    (oal_atomic_sub_return(1, v))
#define oal_atomic_sub_and_test(i, v) (oal_atomic_sub_return(i, v) == 0)

#define        oal_bit_atomic_for_each_set(bit, addr,size)    \
            for ((bit) = find_next_bit((addr), (size), 0);      \
         (bit) < (size);                    \
         (bit) = find_next_bit((addr), (size), (bit) + 1))

/* same as for_each_set_bit() but use bit as value to start with *



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/



#if __LINUX_ARM_ARCH__ >= 6

/*
 * ARMv6 UP and SMP safe atomic ops.  We use load exclusive and
 * store exclusive to ensure that these are atomic.  We may loop
 * to ensure that the update happens.
 */
static inline void atomic_add(int i, oal_atomic *v)
{
    unsigned long tmp;
    int result;

    __asm__ __volatile__("@ atomic_add\n"
"1: ldrex   %0, [%2]\n"
"   add %0, %0, %3\n"
"   strex   %1, %0, [%2]\n"
"   teq %1, #0\n"
"   bne 1b"
    : "=&r" (result), "=&r" (tmp)
    : "r" (&v->counter), "Ir" (i)
    : "cc");
}

static inline int atomic_add_return(int i, oal_atomic *v)
{
    unsigned long tmp;
    int result;

    smp_mb();

    __asm__ __volatile__("@ atomic_add_return\n"
"1: ldrex   %0, [%2]\n"
"   add %0, %0, %3\n"
"   strex   %1, %0, [%2]\n"
"   teq %1, #0\n"
"   bne 1b"
    : "=&r" (result), "=&r" (tmp)
    : "r" (&v->counter), "Ir" (i)
    : "cc");

    smp_mb();

    return result;
}

static inline void atomic_sub(int i, oal_atomic *v)
{
    unsigned long tmp;
    int result;

    __asm__ __volatile__("@ atomic_sub\n"
"1: ldrex   %0, [%2]\n"
"   sub %0, %0, %3\n"
"   strex   %1, %0, [%2]\n"
"   teq %1, #0\n"
"   bne 1b"
    : "=&r" (result), "=&r" (tmp)
    : "r" (&v->counter), "Ir" (i)
    : "cc");
}

static inline int atomic_sub_return(int i, oal_atomic *v)
{
    unsigned long tmp;
    int result;

    smp_mb();

    __asm__ __volatile__("@ atomic_sub_return\n"
"1: ldrex   %0, [%2]\n"
"   sub %0, %0, %3\n"
"   strex   %1, %0, [%2]\n"
"   teq %1, #0\n"
"   bne 1b"
    : "=&r" (result), "=&r" (tmp)
    : "r" (&v->counter), "Ir" (i)
    : "cc");

    smp_mb();

    return result;  
}

#else /* ARM_ARCH_6 */

#ifdef CONFIG_SMP
#error SMP not supported on pre-ARMv6 CPUs
#endif

static inline int oal_atomic_add_return(int i, oal_atomic *v)
{
    UINTPTR uvIntSave;
    int val;

    uvIntSave = LOS_IntLock();
    val = v->counter;
    v->counter = val += i;
    (VOID)LOS_IntRestore(uvIntSave);

    return val; 
}
#define oal_atomic_add(i, v)    (void) oal_atomic_add_return(i, v)

static inline int oal_atomic_sub_return(int i, oal_atomic *v)
{
    UINTPTR uvIntSave;
    int val;

    uvIntSave = LOS_IntLock();
    val = v->counter;
    v->counter = val -= i;
    (VOID)LOS_IntRestore(uvIntSave);

    return val; 
}
#define oal_atomic_sub(i, v)    (void) oal_atomic_sub_return(i, v)

#endif 

OAL_STATIC OAL_INLINE unsigned long __ffs(unsigned long word)
{
    int num = 0;

#if BITS_PER_LONG == 64
    if ((word & 0xffffffff) == 0) {
        num += 32;
        word >>= 32;
    }
#endif
    if ((word & 0xffff) == 0) {
        num += 16;
        word >>= 16;
    }
    if ((word & 0xff) == 0) {
        num += 8;
        word >>= 8;
    }
    if ((word & 0xf) == 0) {
        num += 4;
        word >>= 4;
    }
    if ((word & 0x3) == 0) {
        num += 2;
        word >>= 2;
    }
    if ((word & 0x1) == 0)
        num += 1;
    return num;
}


OAL_STATIC OAL_INLINE oal_bitops find_next_bit(const oal_bitops *addr, oal_bitops size,
                oal_bitops offset)
{
    const oal_bitops *p = addr + BITOP_WORD(offset);
    oal_bitops result = offset & ~(BITS_PER_LONG-1);
    oal_bitops tmp;

    if (offset >= size)
        return size;
    size -= result;
    offset %= BITS_PER_LONG;
    if (offset) {
        tmp = *(p++);
        tmp &= (~0UL << offset);
        if (size < BITS_PER_LONG)
            goto found_first;
        if (tmp)
            goto found_middle;
        size -= BITS_PER_LONG;
        result += BITS_PER_LONG;
    }
    while (size & ~(BITS_PER_LONG-1)) {
        if ((tmp = *(p++)))
            goto found_middle;
        result += BITS_PER_LONG;
        size -= BITS_PER_LONG;
    }
    if (!size)
        return result;
    tmp = *p;

found_first:
    tmp &= (~0UL >> (BITS_PER_LONG - size));
    if (tmp == 0UL)     /* Are any bits set? */
        return result + size;   /* Nope. */
found_middle:
    return result + __ffs(tmp);
}

OAL_STATIC OAL_INLINE oal_void  oal_bit_atomic_set(oal_int32 nr, OAL_VOLATILE oal_bitops *p_addr)
{
    UINTPTR uvIntSave;
    uvIntSave = LOS_IntLock();
    
    oal_bitops mask = BIT_MASK(nr);
    oal_bitops *p = ((oal_bitops *)p_addr) + BIT_WORD(nr);
    *p  |= mask;

    (VOID)LOS_IntRestore(uvIntSave);
}

OAL_STATIC OAL_INLINE oal_int32  oal_bit_atomic_test(oal_int32 nr, OAL_VOLATILE oal_bitops *p_addr)
{
    return 1UL & (p_addr[BIT_WORD(nr)] >> (nr & (BITS_PER_LONG-1)));
}

/*****************************************************************************
 函 数 名  : oal_bit_atomic_test_and_set
 功能描述  : 原子的对某个位进行置1操作，并返回该位置的旧值。
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
OAL_STATIC OAL_INLINE oal_bitops  oal_bit_atomic_test_and_set(oal_int32 nr, OAL_VOLATILE oal_bitops *p_addr)
{
    UINTPTR uvIntSave;
    uvIntSave = LOS_IntLock();
    
    oal_bitops mask = BIT_MASK(nr);
    oal_bitops *p = ((oal_bitops *)p_addr) + BIT_WORD(nr);
    oal_bitops old = *p;
    *p = old | mask;

    (VOID)LOS_IntRestore(uvIntSave);
    return ((old & mask) != 0);
}


OAL_STATIC OAL_INLINE oal_bitops  oal_bit_atomic_test_and_clear(oal_int32 nr, OAL_VOLATILE oal_bitops *p_addr)
{
    UINTPTR uvIntSave;
    uvIntSave = LOS_IntLock();
    
    oal_bitops mask = BIT_MASK(nr);
    oal_bitops *p = ((oal_bitops *)p_addr) + BIT_WORD(nr);
    oal_bitops old = *p;
    *p = old & ~mask;

    (VOID)LOS_IntRestore(uvIntSave);
    return (old & mask) != 0;   
}

/*****************************************************************************
 函 数 名  : oal_bit_atomic_clear
 功能描述  : 封装各个操作系统平台下对某个位进行原子清0操作。
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
OAL_STATIC OAL_INLINE oal_void  oal_bit_atomic_clear(oal_int32 nr, OAL_VOLATILE oal_bitops *p_addr)
{
    UINTPTR uvIntSave;
    uvIntSave = LOS_IntLock();
    
    oal_bitops mask = BIT_MASK(nr);
    oal_bitops *p = ((oal_bitops *)p_addr) + BIT_WORD(nr);
    *p &= ~mask;
    
    (VOID)LOS_IntRestore(uvIntSave);    
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_atomic.h */


