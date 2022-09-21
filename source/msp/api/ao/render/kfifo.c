#include <string.h>

#include "hi_drv_ao.h"
#include "kfifo.h"
#include "render_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define min(a,b) (a <= b ? a : b)
#define is_power_of_2(x) ((x) != 0 && (((x) & ((x) - 1)) == 0))

int kfifo_init(kfifo_s* fifo, void* data, unsigned int size)
{
    if ((NULL == data) || (!is_power_of_2(size)))
    {
        return -1;
    }

    fifo->in  = 0;
    fifo->out = 0;
    fifo->size = size;
    fifo->data = data;

    return 0;
}

void kfifo_deinit(kfifo_s* fifo)
{
    fifo->in  = 0;
    fifo->out = 0;
    fifo->size = 0;
    fifo->data = NULL;
}

void kfifo_reset(kfifo_s* fifo)
{
    memset(fifo->data, 0, fifo->size);
    fifo->in = 0;
    fifo->out = 0;
}

unsigned int kfifo_availabe(kfifo_s* fifo)
{
    return (fifo->in >= fifo->out) ? (fifo->size - fifo->in + fifo->out) : (fifo->out - fifo->in);
}

unsigned int kfifo_busy(kfifo_s* fifo)
{
    return (fifo->size - kfifo_availabe(fifo));
}

unsigned int kfifo_linear_availabe(kfifo_s* fifo)
{
    return (fifo->in >= fifo->out) ? (fifo->size - fifo->in) : (fifo->out - fifo->in);
}

unsigned int kfifo_size(kfifo_s* fifo)
{
    return fifo->size;
}

unsigned int kfifo_write(kfifo_s* fifo, const void* buf, const unsigned int len)
{
    unsigned int l;

    if (kfifo_availabe(fifo) <= len)  /* buffer cannot be full filled for identify the buf state */
    {
        CHANNEL_PRINTF("needsize:%d  kfifo_availabe %d \n", len, kfifo_availabe(fifo));
        return -1;
    }

    l = min(len, fifo->size - fifo->in);

    memcpy((char*)fifo->data + fifo->in, buf, l);
    memcpy(fifo->data, (char*)buf + l, len - l);

    kfifo_update_write_ptr(fifo, len);

    return 0;
}

void kfifo_get_write_ptr(kfifo_s* fifo, void** buf)
{
    *buf = fifo->data + fifo->in;
}

void kfifo_update_write_ptr(kfifo_s* fifo, const unsigned int len)
{
    fifo->in = (fifo->in + len) & (fifo->size - 1);
}

int kfifo_read(kfifo_s* fifo, void* buf, const unsigned int len)
{
    unsigned int l;

    if (kfifo_busy(fifo) < len)
    {
        return -1;
    }

    l = min(len, fifo->size - fifo->out);

    memcpy(buf, (char*)fifo->data + fifo->out, l);
    memcpy((char*)buf + l , fifo->data, len - l);

    kfifo_update_read_ptr(fifo, len);

    return 0;
}

void kfifo_update_read_ptr(kfifo_s* fifo, const unsigned int len)
{
    fifo->out = (fifo->out + len) & (fifo->size - 1);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
