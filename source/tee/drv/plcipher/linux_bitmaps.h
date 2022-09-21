/******************************************************************************

  Copyright (C), 2011-2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : linux_bitmaps.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __PLCIPHER_LINUX_BITMAPS_H__
#define __PLCIPHER_LINUX_BITMAPS_H__

#include "hi_type.h"
#include "hi_tee_debug.h"
#include "tee_plcipher_utils.h"
#include "tee_os_hal.h"

/*
 * linux helpers utils.
 */
#define BITS_PER_BYTE       8
#define BITS_PER_LONG       32
#define BIT_MASK(nr)        (1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)        ((nr) / BITS_PER_LONG)
#define DIV_ROUND_UP(n,d)   (((n) + (d) - 1) / (d))
#define BITS_TO_LONGS(nr)   DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))
#define DECLARE_BITMAP(name,bits) \
                        unsigned long name[BITS_TO_LONGS(bits)]

#define unlikely(condition) (condition)

struct plcipher_mutex {
    struct tee_hal_mutex rlock;
};

#define BUG_ON(condition) if(condition) {HI_ERR_PLCIPHER("BUG ...\n");while(1);}


/*
 * bitmap function helpers refer to linux implementation.
 */
static inline void bitmap_zero(unsigned long *dst, int nbits)
{
    int len = BITS_TO_LONGS(nbits) * sizeof(unsigned long);
    memset(dst, 0, len);
}

static inline void bitmap_setbit(int nr, volatile unsigned long *addr)
{
    unsigned long mask = BIT_MASK(nr);
    unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);

    *p  |= mask;
}

static inline void bitmap_clrbit(int nr, volatile unsigned long *addr)
{
    unsigned long mask = BIT_MASK(nr);
    unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);

    *p &= ~mask;
}

static unsigned long __ffs(unsigned long word)
{
    int num = 0;

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

#define ffz(x) __ffs( ~(x) )

static inline unsigned long find_first_zero_bit(const unsigned long *addr, unsigned long size)
{
    const unsigned long *p = addr;
    unsigned long result = 0;
    unsigned long tmp;

    while (size & ~(BITS_PER_LONG-1)) {
        if (~(tmp = *(p++)))
            goto found;
        result += BITS_PER_LONG;
        size -= BITS_PER_LONG;
    }
    if (!size)
        return result;

    tmp = (*p) | (~0UL << size);
    if (tmp == ~0UL)    /* Are any bits zero? */
        return result + size;   /* Nope. */
found:
    return result + ffz(tmp);
}

static inline unsigned long find_first_bit(const unsigned long *addr, unsigned long size)
{
    const unsigned long *p = addr;
    unsigned long result = 0;
    unsigned long tmp;

    while (size & ~(BITS_PER_LONG-1)) {
        if ((tmp = *(p++)))
            goto found;
        result += BITS_PER_LONG;
        size -= BITS_PER_LONG;
    }
    if (!size)
        return result;

    tmp = (*p) & (~0UL >> (BITS_PER_LONG - size));
    if (tmp == 0UL)  /* Are any bits set? */
        return result + size;   /* Nope. */
found:
    return result + __ffs(tmp);
}

#define BITOP_WORD(nr)    ((nr) / BITS_PER_LONG)
static inline unsigned long find_next_bit(const unsigned long *addr, unsigned long size,
                unsigned long offset)
{
    const unsigned long *p = addr + BITOP_WORD(offset);
    unsigned long result = offset & ~(BITS_PER_LONG-1);
    unsigned long tmp;

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

#define for_each_set_bit(bit, addr, size) \
    for ((bit) = find_first_bit((addr), (size));        \
         (bit) < (size);                    \
         (bit) = find_next_bit((addr), (size), (bit) + 1))

//extern int snprintf (char *, unsigned int, const char *, ...);

static inline void plcipher_mutex_init(struct plcipher_mutex *lock)
{
    HI_S32 ret;
    HI_CHAR str[10] = {0};

    snprintf(str, sizeof(str), "%x", lock);

    ret = tee_hal_mutex_init(str, &lock->rlock);
    if (ret)
    {
        HI_ERR_PLCIPHER("Create mutex failed(0x%x).\n", ret);
    }
}

static inline void plcipher_mutex_lock(struct plcipher_mutex *lock)
{
    tee_hal_mutex_lock(&lock->rlock);
}

static inline void plcipher_mutex_unlock(struct plcipher_mutex *lock)
{
    tee_hal_mutex_unlock(&lock->rlock);
}
/*
 * it can't adapt this function in secureos , so it always return true;
 */
static inline int plcipher_mutex_is_locked(struct plcipher_mutex *lock)
{
    return 1;
}

/*
 * it can't been interruptibled in secureos, so it's just wrapper of plcipher_mutex_lock.
 */
static inline int plcipher_mutex_lock_interruptible(struct plcipher_mutex *lock)
{
    plcipher_mutex_lock(lock);

    return 0;
}

#endif      /* __PLCIPHER_LINUX_BITMAPS_H__ */
