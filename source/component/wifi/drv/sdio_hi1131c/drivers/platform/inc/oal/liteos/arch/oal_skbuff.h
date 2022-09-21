/*
 *  Definitions for the 'struct sk_buff' memory handlers.
 *
 *  Authors:
 *      Alan Cox, <gw4pts@gw4pts.ampr.org>
 *      Florian La Roche, <rzsfl@rz.uni-sb.de>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version
 *  2 of the License, or (at your option) any later version.
 */

#ifndef _LITEOS_SKBUFF_H
#define _LITEOS_SKBUFF_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <linux/spinlock.h>
#include "los_memory.h"

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <linux/kernel.h>
#include <asm/page.h>
#include "oal_types.h"
#include "oal_atomic.h"


/* Don't change this without changing skb_csum_unnecessary! */
#define CHECKSUM_NONE 0
#define CHECKSUM_UNNECESSARY 1
#define CHECKSUM_COMPLETE 2
#define CHECKSUM_PARTIAL 3

#define L1_CACHE_BYTES      (1 << 5)
#define SMP_CACHE_BYTES L1_CACHE_BYTES

#define SKB_DATA_ALIGN(X)   (((X) + (SMP_CACHE_BYTES - 1)) & \
                 ~(SMP_CACHE_BYTES - 1))
/*#define SKB_WITH_OVERHEAD(X)  \
    ((X) - SKB_DATA_ALIGN(sizeof(struct skb_shared_info)))*/
#define SKB_MAX_ORDER(X, ORDER) \
    SKB_WITH_OVERHEAD((PAGE_SIZE << (ORDER)) - (X))
#define SKB_MAX_HEAD(X)     (SKB_MAX_ORDER((X), 0))
#define SKB_MAX_ALLOC       (SKB_MAX_ORDER(0, 2))

/* return minimum truesize of one skb containing X bytes of data */
#define SKB_TRUESIZE(X) ((X) +                      \
             SKB_DATA_ALIGN(sizeof(struct sk_buff)))

#define max(x,y) (x<y?y:x)
#ifndef NET_SKB_PAD
#define NET_SKB_PAD 64//max(32, L1_CACHE_BYTES)
#endif


#define GFP_ATOMIC  (0)
#define NUMA_NO_NODE    (-1)

#define USB_CACHE_ALIGN_SIZE 32
typedef unsigned int gfp_t;

typedef unsigned int sk_buff_data_t;

struct sk_buff_head {
    /* These two members must be first. */
    struct sk_buff  *next;
    struct sk_buff  *prev;

    unsigned int        qlen;
    spinlock_t  lock;
};


struct sk_buff {
    /* These two members must be first. */
    struct sk_buff      *next;
    struct sk_buff      *prev;

    /*struct sock       *sk;*/
    //struct net_device *dev;
    void    *dev;//for hwal_netif_rx


    unsigned int        len,
                        data_len;

    unsigned short      queue_mapping;

    unsigned int        headers_start[0];

    unsigned int        headers_end[0];

    /* These elements must be at the end, see alloc_skb() for details.  */
    sk_buff_data_t      tail;
    sk_buff_data_t      end;

    char                cb[48];
    unsigned char       *head,
                        *data;

    unsigned int        truesize;
    unsigned int        priority;
    oal_atomic          users;

    //unsigned int        pkt_type;
    unsigned char       *p_mem_head;  // use for lwip_pbuf zero_copy:actual start addr of memory space
    unsigned int        protocol;

    unsigned short      mac_header;

};

#define SKB_ALLOC_FCLONE    0x01
#define SKB_ALLOC_RX        0x02


#define skb_queue_walk(queue, skb) \
                for (skb = (queue)->next;                                       \
                     skb != (struct sk_buff *)(queue);                          \
                     skb = skb->next)

#define skb_queue_walk_safe(queue, skb, tmp)                                    \
                for (skb = (queue)->next, tmp = skb->next;                      \
                     skb != (struct sk_buff *)(queue);                          \
                     skb = tmp, tmp = skb->next)


static inline bool skb_pfmemalloc(const struct sk_buff *skb)
{
    return false;
}

static inline void __skb_queue_head_init(struct sk_buff_head *list)
{
    list->prev = list->next = (struct sk_buff *)list;
    list->qlen = 0;
}

static inline void skb_queue_head_init(struct sk_buff_head *list)
{
    spin_lock_init(&list->lock);
    __skb_queue_head_init(list);
}

static inline void skb_reset_tail_pointer(struct sk_buff *skb)
{
    skb->tail = skb->data - skb->head;
}

#define offsetof(type, member) ((long) &((type *) 0)->member)

static inline unsigned char *skb_tail_pointer(const struct sk_buff *skb)
{
    unsigned char *phead = skb->head;
    return (phead + skb->tail);
}

static inline int skb_queue_empty(const struct sk_buff_head *list)
{
    return list->next == (struct sk_buff *)list;
}

static inline void skb_reserve(struct sk_buff *skb, int len)
{
    skb->data += len;
    skb->tail += len;
}

static inline unsigned char *skb_mac_header(const struct sk_buff  *skb)
{
      return skb->data;
}

extern struct sk_buff *alloc_skb(unsigned int size, gfp_t priority);

struct sk_buff *skb_copy(const struct sk_buff *skb, gfp_t priority);

static inline struct sk_buff *__dev_alloc_skb(unsigned int length,
                          gfp_t gfp_mask)
{
    struct sk_buff *skb = alloc_skb(length + NET_SKB_PAD, gfp_mask);
    if (skb != NULL)
        skb_reserve(skb, NET_SKB_PAD);
    return skb;
}


void skb_unlink(struct sk_buff *skb, struct sk_buff_head *list);
static inline void __skb_unlink(struct sk_buff *skb, struct sk_buff_head *list)
{
    struct sk_buff *next, *prev;

    list->qlen--;
    next       = skb->next;
    prev       = skb->prev;
    skb->next  = skb->prev = NULL;
    next->prev = prev;
    prev->next = next;
}

static inline struct sk_buff *skb_get(struct sk_buff *skb)
{
    oal_atomic_inc(&skb->users);
    return skb;
}

static inline struct sk_buff *skb_peek(const struct sk_buff_head *list_)
{
    struct sk_buff *list = ((const struct sk_buff *)list_)->next;
    if (list == (struct sk_buff *)list_)
        list = NULL;
    return list;
}

static inline struct sk_buff *skb_peek_next(struct sk_buff *skb,
        const struct sk_buff_head *list_)
{
    struct sk_buff *next = skb->next;

    if (next == (struct sk_buff *)list_)
        next = NULL;
    return next;
}

static inline struct sk_buff *skb_peek_tail(const struct sk_buff_head *list_)
{
    struct sk_buff *skb = list_->prev;

    if (skb == (struct sk_buff *)list_)
        skb = NULL;
    return skb;

}

extern struct sk_buff *skb_dequeue(struct sk_buff_head *list);
static inline struct sk_buff *__skb_dequeue(struct sk_buff_head *list)
{
    struct sk_buff *skb = skb_peek(list);
    if (skb)
        __skb_unlink(skb, list);
    return skb;
}

struct sk_buff *skb_dequeue_tail(struct sk_buff_head *list);
static inline struct sk_buff *__skb_dequeue_tail(struct sk_buff_head *list)
{
    struct sk_buff *skb = skb_peek_tail(list);
    if (skb)
        __skb_unlink(skb, list);
    return skb;
}

static inline unsigned int skb_headlen(const struct sk_buff *skb)
{
    return skb->len - skb->data_len;
}

static inline void __skb_insert(struct sk_buff *newsk,
                struct sk_buff *prev, struct sk_buff *next,
                struct sk_buff_head *list)
{
    newsk->next = next;
    newsk->prev = prev;
    next->prev  = prev->next = newsk;
    list->qlen++;
}

static inline void __skb_queue_before(struct sk_buff_head *list,
                      struct sk_buff *next,
                      struct sk_buff *newsk)
{
    __skb_insert(newsk, next->prev, next, list);
}


extern void skb_queue_tail(struct sk_buff_head *list, struct sk_buff *newsk);
static inline void __skb_queue_tail(struct sk_buff_head *list,
                   struct sk_buff *newsk)
{
    __skb_queue_before(list, (struct sk_buff *)list, newsk);
}

static inline oal_uint32 skb_queue_len(const struct sk_buff_head *list_)
{
    return list_->qlen;
}

static inline void __skb_queue_splice(const struct sk_buff_head *list,
                      struct sk_buff *prev,
                      struct sk_buff *next)
{
    struct sk_buff *first = list->next;
    struct sk_buff *last = list->prev;

    first->prev = prev;
    prev->next = first;

    last->next = next;
    next->prev = last;
}

static inline void skb_queue_splice(const struct sk_buff_head *list,
                    struct sk_buff_head *head)
{
    if (!skb_queue_empty(list)) {
        __skb_queue_splice(list, (struct sk_buff *) head, head->next);
        head->qlen += list->qlen;
    }
}

static inline void skb_queue_splice_tail_init(struct sk_buff_head *list,
                          struct sk_buff_head *head)
{
    if (!skb_queue_empty(list)) {
        __skb_queue_splice(list, head->prev, (struct sk_buff *) head);
        head->qlen += list->qlen;
        __skb_queue_head_init(list);
    }
}

static inline void skb_queue_splice_init(struct sk_buff_head *list,
                     struct sk_buff_head *head)
{
    if (!skb_queue_empty(list)) {
        __skb_queue_splice(list, (struct sk_buff *) head, head->next);
        head->qlen += list->qlen;
        __skb_queue_head_init(list);
    }
}

extern unsigned char *skb_pull(struct sk_buff *skb, unsigned int len);
static inline unsigned char *__skb_pull(struct sk_buff *skb, unsigned int len)
{
    skb->len -= len;
    BUG_ON(skb->len < skb->data_len);
    return skb->data += len;
}

static inline unsigned char *skb_pull_inline(struct sk_buff *skb, unsigned int len)
{
    return unlikely(len > skb->len) ? NULL : __skb_pull(skb, len);
}

static inline unsigned int skb_headroom(const struct sk_buff *skb)
{
    return skb->data - skb->head;
}

static inline bool skb_is_nonlinear(const struct sk_buff *skb)
{
    return skb->data_len;
}

static inline void skb_copy_from_linear_data_offset(const struct sk_buff *skb,
                            const int offset, void *to,
                            const unsigned int len)
{
    memcpy(to, skb->data + offset, len);
}

static inline void skb_set_tail_pointer(struct sk_buff *skb, const int offset)
{
    skb_reset_tail_pointer(skb);
    skb->tail += offset;
}

static inline void __skb_trim(struct sk_buff *skb, unsigned int len)
{
    if (unlikely(skb_is_nonlinear(skb))) {
        WARN_ON(1);
        return;
    }
    skb->len = len;
    skb_set_tail_pointer(skb, len);
}

static inline unsigned char *skb_push(struct sk_buff *skb, unsigned int len)
{
    if(skb->data - len < skb->head)
    {
        printk("skb_push error! \r\n");
        return NULL;
    }

    skb->data -= len;
    skb->len  += len;
    return skb->data;
}

static inline int skb_tailroom(const struct sk_buff *skb)
{
    return skb_is_nonlinear(skb) ? 0 : skb->end - skb->tail;
}

static inline bool skb_queue_is_last(const struct sk_buff_head *list,
                     const struct sk_buff *skb)
{
    return skb->next == (struct sk_buff *)list;
}

static inline unsigned char *skb_end_pointer(const struct sk_buff *skb)
{
    return skb->head + skb->end;
}

static inline unsigned int skb_end_offset(const struct sk_buff *skb)
{
    return skb->end;
}

void dev_kfree_skb(struct sk_buff *skb);
#define dev_kfree_skb_any(a) dev_kfree_skb(a)

#define skb_queue_walk(queue, skb) \
        for (skb = (queue)->next;                   \
             skb != (struct sk_buff *)(queue);              \
             skb = skb->next)


struct sk_buff *dev_alloc_skb(unsigned int length);
unsigned char *skb_put(struct sk_buff *skb, unsigned int len);
void skb_queue_purge(struct sk_buff_head *list);
static inline void __skb_queue_after(struct sk_buff_head *list,
                     struct sk_buff *prev,
                     struct sk_buff *newsk)
{
    __skb_insert(newsk, prev, prev->next, list);
}

static inline void __skb_queue_head(struct sk_buff_head *list,
                    struct sk_buff *newsk)
{
    __skb_queue_after(list, (struct sk_buff *)list, newsk);
}


static inline void skb_set_queue_mapping(struct sk_buff *skb,
                    unsigned short queue_mapping)
{
    skb->queue_mapping = queue_mapping;
}

static inline unsigned short skb_get_queue_mapping(const struct sk_buff *skb)
{
    return skb->queue_mapping;
}

static inline void skb_copy_queue_mapping(struct sk_buff *to,
                    const struct sk_buff *from)
{
    to->queue_mapping = from->queue_mapping;
}

int pskb_may_pull(struct sk_buff *skb, unsigned int len);
struct sk_buff *skb_unshare(struct sk_buff *skb, gfp_t pri);

#endif  /* _LITEOS_SKBUFF_H */
