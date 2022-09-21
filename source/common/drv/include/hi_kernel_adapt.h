#ifndef __HI_KERNEL_ADAPT_H__
#define __HI_KERNEL_ADAPT_H__

#include <linux/version.h>
#include <linux/dma-buf.h>
#include <linux/interrupt.h>
#include <linux/irq.h>


#define HI_DECLARE_MUTEX(x) DEFINE_SEMAPHORE(x)

#define HI_INIT_MUTEX(x)    sema_init(x, 1)

struct osal_dma_buf_export_info {
    const char *exp_name;
    struct module *owner;
    const struct dma_buf_ops *ops;
    size_t size;
    int flags;
    struct reservation_object *resv;
    void *priv;
};
extern  struct dma_buf *osal_dma_buf_export(const struct osal_dma_buf_export_info *exp_info);

//typedef int (*osal_irq_handler_t)(int, void *);
extern int osal_request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags,const char *name, void *dev);
extern void osal_free_irq(unsigned int irq, const char *name, void *dev);


#endif

