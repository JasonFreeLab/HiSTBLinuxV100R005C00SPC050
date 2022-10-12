#ifndef __HI_IRQS_H__
#define __HI_IRQS_H__

#define HISI_GIC_IRQ_START      (32)
#define IRQ_LOCALTIMER          (29)
#define INTNR_COMMTX0           (HISI_GIC_IRQ_START + 0)
#define INTNR_COMMRX0           (HISI_GIC_IRQ_START + 2)
#define INTNR_WATCHDOG          (HISI_GIC_IRQ_START + 4)
#define INTNR_TIMER_0_1         (HISI_GIC_IRQ_START + 24)
#define INTNR_TIMER_2           (HISI_GIC_IRQ_START + 25)
#define INTNR_TIMER_3           (HISI_GIC_IRQ_START + 58)
#define INTNR_TIMER_4           (HISI_GIC_IRQ_START + 26)
#define INTNR_TIMER_5           (HISI_GIC_IRQ_START + 59)
#define INTNR_TIMER_6           (HISI_GIC_IRQ_START + 27)
#define INTNR_TIMER_7           (HISI_GIC_IRQ_START + 60)

#define INTNR_I2C0              (HISI_GIC_IRQ_START + 22)
#define INTNR_I2C1              (HISI_GIC_IRQ_START + 23)
#define INTNR_I2C2              (HISI_GIC_IRQ_START + 24)
#define INTNR_I2C3              (HISI_GIC_IRQ_START + 25)
#define INTNR_UART0             (HISI_GIC_IRQ_START + 49)
#define INTNR_UART1             (HISI_GIC_IRQ_START + 50)
#define INTNR_UART2             (HISI_GIC_IRQ_START + 51)
#define INTNR_UART3             (HISI_GIC_IRQ_START + 52)
#define INTNR_UART4             (HISI_GIC_IRQ_START + 53)

#define INTNR_ETH               (HISI_GIC_IRQ_START + 51)
#define INTNR_L2CACHE_CHK0_INT  (HISI_GIC_IRQ_START + 72)
#define INTNR_L2CACHE_CHK1_INT  (HISI_GIC_IRQ_START + 73)
#define INTNR_L2CACHE_INT_COMB  (HISI_GIC_IRQ_START + 74)
#define INTNR_A9_PMU_INT0       (HISI_GIC_IRQ_START + 8)
#define INTNR_A9_PMU_INT1       (HISI_GIC_IRQ_START + 9)

/* HISI_GIC_IRQ_START+160  ~  HISI_GIC_IRQ_START+320  reserve for gpio dynamic irq*/
#define NR_IRQS                 (HISI_GIC_IRQ_START + 320)
#define MAX_GIC_NR              1

#endif
