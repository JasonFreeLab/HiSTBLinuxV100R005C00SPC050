#ifndef __TIMER_H__
#define __TIMER_H__


/* function */
extern void timer_resetParam(void);
extern void TIMER_Enable(void);
extern void TIMER_Disable(void);
extern void TIMER_Init(void);
extern void timer_getParam(void);
extern void TIMER_Isr(void);
#endif
