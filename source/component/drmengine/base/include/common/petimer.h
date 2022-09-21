/**
 * Copyright (C), 2005, Hisilicon Tech. Co., Ltd.
 *
 */

#ifndef __PETIMER_H__
#define __PETIMER_H__

#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

typedef void * petimer_t;

#define PETF_AUTO_RESTART   0x0  /* the timer re-arms itself */
#define PETF_ONE_SHOOT      0x1  /* the timer start once and then stop */
#define PETF_AUTO_FREE      0x2  /* the timer start once and then free */

/**
 * start the whole timer system. see README for detail.
 *
 * @param thread space to hold thread id created by the function
 * @param attr attribute for creating the thread
 * @return errno
 */
extern int petimer_start(pthread_t * thread, pthread_attr_t * attr, void **sync);

/**
 * create an absolute/relative timer.
 *
 * @param timeout the timeout function, it cannot be NULL
 * @param flag combination of PETF_ONE_SHOOT and PETF_AUTO_FREE
 * @return the time created
 */
extern petimer_t petimer_create_abstimer(void (*timeout)(void *), int flag);
extern petimer_t petimer_create_reltimer(void (*timeout)(void *), int flag);

/**
 * free an absolute/relative timer.
 *
 * @param timer the timer to free
 */
extern int petimer_free_abstimer(void *sync_block, petimer_t timer);
extern int petimer_free_reltimer(void *sync_block, petimer_t timer);

/**
 * start/restart an absolute/relative timer. restart happend if the timer is
 * already started.
 *
 * @param timer the timer to start
 * @param tm the time to start. only tm_sec, tm_min, tm_hour, tm_mday, tm_mon and
 *           tm_year are senceness, the other fields are ignored. you may set a
 *           field to -1, it means it can be anytime to match. Therefore, if you
 *           need a timer to expired at 10:00am every day, you may set
 *           tm_sec=0 tm_min=0 tm_hour=10 tm_mday=-1 tm_mon=-1 tm_year=-1.
 *           man 3 localtime for more detail of this field, you may have not notice
 *           that the tm_year is not the same with the current year number.
 * @param msec millisecond to start the timer, if it is zero, the timer expired
 *             when next tick come
 * @param arg the argument to start the timer
 * @return errno
 */
extern int petimer_start_abstimer(void *sync_blk, petimer_t timer, struct tm * tm, void * arg);
extern int petimer_start_reltimer(void *sync_blk, petimer_t timer, unsigned int msec, void * arg);

/**
 * stop an absolute timer.
 *
 * @param the timer to stop
 * @param finallize a function to finallize your own resource
 * @param arg argument for the finallize function
 * @return errno
 */
extern int petimer_stop_abstimer_safe(void *sync_block, petimer_t timer, void (*finallize)(void *), void * arg);
extern int petimer_stop_reltimer_safe(void *sync_block, petimer_t timer, void (*finallize)(void *), void * arg);
#define petimer_stop_abstimer(sync_block, timer) petimer_stop_abstimer_safe(timer, NULL, NULL);
#define petimer_stop_reltimer(sync_block, timer) petimer_stop_reltimer_safe(timer, NULL, NULL);

/**
 * like:
 * petimer_start_reltimer(petimer_create_reltimer(mesc, PETF_AUTO_FREE), timeout, arg);
 */
int petimer_start_reltimer_simple(void *sync_block, unsigned int msec, void (*timeout)(void *), void * arg);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif  /* __cplusplus */

#endif /* __PETIMER_H__ */

/**
 * 20030614 0.1 kenny create
 *
 * vi: set expandtab tabstop=4:
 */
