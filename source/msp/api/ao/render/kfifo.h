#ifndef __KFIFO_H__
#define __KFIFO_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

typedef struct
{
    unsigned int      in;
    unsigned int     out;
    unsigned int    size;
    void*           data;
} kfifo_s;

int kfifo_init(kfifo_s* fifo, void* data, unsigned int size);

void kfifo_deinit(kfifo_s* fifo);

void kfifo_reset(kfifo_s* fifo);

unsigned int kfifo_availabe(kfifo_s* fifo);

unsigned int kfifo_busy(kfifo_s* fifo);

unsigned int kfifo_linear_availabe(kfifo_s* fifo);

unsigned int kfifo_size(kfifo_s* fifo);

unsigned int kfifo_write(kfifo_s* fifo, const void* buf, const unsigned int len);

void kfifo_get_write_ptr(kfifo_s* fifo, void** buf);

void kfifo_update_write_ptr(kfifo_s* fifo, const unsigned int len);

int kfifo_read(kfifo_s* fifo, void* buf, const unsigned int len);

void kfifo_update_read_ptr(kfifo_s* fifo, const unsigned int len);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif
