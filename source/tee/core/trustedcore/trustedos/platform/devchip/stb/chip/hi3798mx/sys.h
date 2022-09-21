#ifndef HI3798MX_SYS_H
#define HI3798MX_SYS_H

#define REG_BASE_SCTRL          (0xF8000000)       //SCTRL
#define REG_BASE_PERI_CRG       (0xF8A20000)       //PERI_CRG

#define REG_BASE_GIC_CPU       (0xF8A02000)
#define REG_BASE_GIC_DIS	   (0xF8A01000)

#define SAVE_CTX_OFFSET             68
#define STORE_OFFSET_UNIT           0x200

#define SYS_IO_ADDR_START	0xF0000000
#define SYS_IO_ADDR_END		0xFFFFFFFF

/* RNG register */
#define RNG_REG_BASE                		(0xF8005000)
#define SC_RNG_DATA_CTRL            		(RNG_REG_BASE + 0x0)
#define SC_RNG_DATA_CNT             		(RNG_REG_BASE + 0x8)
#define SC_RNG_DATA_VAL             		(RNG_REG_BASE + 0x4)

#endif /* HI3798MX_SYS_H */