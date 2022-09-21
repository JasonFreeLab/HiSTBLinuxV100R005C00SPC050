#ifndef TIMER_H
#define TIMER_H

#include "hi_list.h"

#define TEST_TIMER  0

#if TEST_TIMER
void sp804_test(void);
#endif
/**
 * struct timer_list - structure which describes a timer
 * the resolution is us
 *
 * @param expires	The expires time in us for the timer
 * @param data		The param pass back to the timer handler
 * @param slack		The delay for the timer if expires when add timer
 * @param function	The callback function of the timer
 * @param entry		The internel list node, not seen by users
 */
struct timer_list {
	unsigned long long expires;
	unsigned long data;
	unsigned long long slack;
	void (*function)(unsigned long);
	struct list_head entry;
};

/**
 * init_timer()	- timer init function
 *
 * @param timer		The timer to be initialized
 */
void init_timer(struct timer_list *timer);

/**
 * add_timer() - timer add function
 *
 * @param timer		The timer to be added
 *
 * @return 0		Success
 * @return other value	Failed
 */
int add_timer(struct timer_list *timer);

/**
 * del_timer() - timer delete function
 *
 * @param timer		The timer to be deleted
 */
void del_timer(struct timer_list *timer);

/**
 * mod_timer() - timer mod function
 *
 * @param timer		The timer to be mod
 * @param expire_us	The expire time in us for the timer
 *
 * @return 0		Success
 * @return other value	Failed
 */
int mod_timer(struct timer_list *timer, unsigned long expire_us);

#endif
