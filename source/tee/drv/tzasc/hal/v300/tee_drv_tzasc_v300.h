#ifndef _TEE_DRV_TZASC_V300_H_
#define _TEE_DRV_TZASC_V300_H_

#define _SEC_BYPASS_BITS_CHIP                    (8)

#define _SEC_RGN_BASE_ADDR_BITS_CHIP              (16)
#define _SEC_RGN_SIZE_SHIFT_CHIP                  (16)
#define _SEC_RGN_SIZE_BITS_CHIP                   (15)
#define _SEC_RGN_SP_SHIFT_CHIP                    (16)
#define _SEC_RGN_SP_BITS_CHIP                     (16)

#define _SEC_SHARE_RGN_FAIL_CMDID_BITS_CHIP       (12)
#define _SEC_SHARE_RGN_FAIL_MID_SHIFT_CHIP        (16)

#define _SEC_LOCKDOWN_SEL_CFG_CHIP   (0x00ff1f0f)

/* TZASC */
#define MAX_REGIONS                             16
/* SHARE region   */
#define MAX_SHARE_REGION                        4

#define SEC_CONFIG                       (TZASC_BASE_ADDR + 0x00)
#define SEC_BYPASS                       (TZASC_BASE_ADDR + 0x04)
#define SEC_LOCKDOWN_SEL                 (TZASC_BASE_ADDR + 0x10)
#define SEC_INT_EN                       (TZASC_BASE_ADDR + 0x20)
#define SEC_INT_STATUS                   (TZASC_BASE_ADDR + 0x24)
#define SEC_INT_CLEAR                    (TZASC_BASE_ADDR + 0x28)
#define SEC_FAIL_ADDRESS_LOW             (TZASC_BASE_ADDR + 0x80)
#define SEC_FAIL_STATUS                  (TZASC_BASE_ADDR + 0x84)
#define SEC_FAIL_ID                      (TZASC_BASE_ADDR + 0x88)

#define SEC_RGN_MAP(x)                   (TZASC_BASE_ADDR + 0x100 + 0x10 * (x))
#define SET_RGN_ATTR(x)                  (TZASC_BASE_ADDR + 0x104 + 0x10 * (x))
#define SET_RGN_MID_W(x)                 (TZASC_BASE_ADDR + 0x108 + 0x10 * (x))
#define SET_RGN_MID_R(x)                 (TZASC_BASE_ADDR + 0x10C + 0x10 * (x))

#define SEC_SHARE_RGN_EN(x)             (TZASC_BASE_ADDR + 0x300 + 0x20 * (x))
#define SEC_SHARE_RGN_START(x)          (TZASC_BASE_ADDR + 0x304 + 0x20 * (x))
#define SEC_SHARE_RGN_END(x)            (TZASC_BASE_ADDR + 0x308 + 0x20 * (x))

#define SEC_MASTER_TYPE_SHARE            (TZASC_BASE_ADDR + 0x30C)
#define SEC_MASTER_TYPE_RSV              (TZASC_BASE_ADDR + 0x310)
#define SEC_SHARE_RGN_FAIL_CMD_STATUS    (TZASC_BASE_ADDR + 0x314)
#define SEC_SHARE_RGN_FAIL_CMD_ADDR      (TZASC_BASE_ADDR + 0x318)
#define SEC_SHARE_RGN_FAIL_ID            (TZASC_BASE_ADDR + 0x31C)

#define TZMA_ROSIZE_REG                        	(TZPC_BASE_ADDR + 0x00)
#define TZASC_RST_REG                          	(TZPC_BASE_ADDR + 0x04)
#define TZASC_SEC_LOCK_REG                      (TZPC_BASE_ADDR + 0x08)
#define CPU_DBG_CTRL_REG                        (TZPC_BASE_ADDR + 0x0c)
#define SEC_ATTR_CTRL_0_REG                     (TZPC_BASE_ADDR + 0x10)
#define SEC_MISC_CTRL_REG                       (TZPC_BASE_ADDR + 0x1c)
#define SEC_DDRC_CTRL_REG                       (TZPC_BASE_ADDR + 0x24)

#define _SEC_NR_RGNS_SHIFT                  (0)
#define _SEC_NR_RGNS_BITS                   (8)
#define _SEC_BYPASS_SHIFT                   (0)
#define _SEC_BYPASS_BITS                    (_SEC_BYPASS_BITS_CHIP)
#define _SEC_INT_EN_SHIFT                   (0)
#define _SEC_INT_EN_BITS                    (1)
#define _SEC_INT_OVERRUN_SHIFT              (1)
#define _SEC_INT_OVERRUN_BITS               (1)
#define _SEC_INT_STATUS_SHIFT               (0)
#define _SEC_INT_STATUS_BITS                (1)
#define _SEC_FAIL_CMD_ADDR_LOW_SHIFT        (0)
#define _SEC_FAIL_CMD_ADDR_BITS             (32)
#define _SEC_FAIL_CMD_ACC_TYPE_SHIFT        (20)
#define _SEC_FAIL_CMD_ACC_TYPE_BITS         (1)
#define _SEC_FAIL_CMD_NS_SHIFT              (17)
#define _SEC_FAIL_CMD_NS_BITS               (1)
#define _SEC_FAIL_CMD_PRVLG_SHIFT           (16)
#define _SEC_FAIL_CMD_PRVLG_BITS            (1)
#define _SEC_FAIL_CMD_ADDR_HIGH_SHIFT       (0)
#define _SEC_FAIL_CMD_ADDR_HIGH_BITS        (8)
#define _SEC_FAIL_CMD_MID_SHIFT             (24)
#define _SEC_FAIL_CMD_MID_BITS              (8)
#define _SEC_FAIL_CMD_ID_SHIFT              (0)
#define _SEC_FAIL_CMD_ID_BITS               (24)
#define _SEC_RGN_BASE_ADDR_SHIFT            (0)
#define _SEC_RGN_BASE_ADDR_BITS             (_SEC_RGN_BASE_ADDR_BITS_CHIP)
#define _SEC_RGN_SIZE_SHIFT                 (_SEC_RGN_SIZE_SHIFT_CHIP)
#define _SEC_RGN_SIZE_BITS                  (_SEC_RGN_SIZE_BITS_CHIP)
#define _SEC_RGN_EN_SHIFT                   (31)
#define _SEC_RGN_EN_BITS                    (1)
#define _SEC_RGN_SP_SHIFT                   (_SEC_RGN_SP_SHIFT_CHIP)
#define _SEC_RGN_SP_BITS                    (_SEC_RGN_SP_BITS_CHIP)
#define _SEC_RGN_SEC_INV_SHIFT              (4)
#define _SEC_RGN_SEC_INV_BITS               (1)
#define _SEC_RGN_MID_EN_SHIFT               (8)
#define _SEC_RGN_MID_EN_BITS                (1)
#define _SEC_RGN_MID_INV_SHIFT              (9)
#define _SEC_RGN_MID_INV_BITS               (1)
#define _SEC_SUBRGN_EN_SHIFT                (16)
#define _SEC_SUBRGN_EN_BITS                 (16)


#define _SEC_SHARE_RGN_EN_SHIFT             (0)
#define _SEC_SHARE_RGN_EN_BITS              (1)
#define _SEC_SHARE_RGN_START_SHIFT          (0)
#define _SEC_SHARE_RGN_START_BITS           (32)
#define _SEC_SHARE_RGN_END_SHIFT            (0)
#define _SEC_SHARE_RGN_END_BITS             (32)
#define _SEC_SHARE_RGN_FAIL_STATUS_SHIFT    (0)
#define _SEC_SHARE_RGN_FAIL_STATUS_BITS     (1)
#define _SEC_SHARE_RGN_FAIL_ADDR_SHIFT      (0)
#define _SEC_SHARE_RGN_FAIL_ADDR_BITS       (32)
#define _SEC_SHARE_RGN_FAIL_CMDID_SHIFT     (0)
#define _SEC_SHARE_RGN_FAIL_CMDID_BITS      (_SEC_SHARE_RGN_FAIL_CMDID_BITS_CHIP)
#define _SEC_SHARE_RGN_FAIL_MID_SHIFT       (_SEC_SHARE_RGN_FAIL_MID_SHIFT_CHIP)
#define _SEC_SHARE_RGN_FAIL_MID_BITS        (5)

#define _SEC_BOOT_LOCK_SHIFT                (0)
#define _SEC_BOOT_LOCK_BITS                 (1)
#define _SEC_ERR_RESP_SHIFT                 (0)
#define _SEC_ERR_RESP_BITS                  (1)

/* Lock qosbuf/axiif/rbc/phy/dmc */
#define _SEC_DDRC_LOCK_CFG     ((1UL<<0) | (1UL<<1) | (1UL<<2) | (1UL<<3) | (1UL<<4))

#define _SEC_LOCKDOWN_SEL_CFG  (_SEC_LOCKDOWN_SEL_CFG_CHIP)

#define TZASC_NON_SECURE_WRITE   (0x5)
#define TZASC_NON_SECURE_READ    (0x5 << 4)
#define TZASC_SECURE_WRITE       (0x5 << 8)
#define TZASC_SECURE_READ        (0x5 << 12)

#define TZASC_SP_NONE		0x0
#define TZASC_SP_NON_SEC	((TZASC_NON_SECURE_WRITE) | (TZASC_NON_SECURE_READ))
#define TZASC_SP_SEC		((TZASC_SECURE_WRITE) | (TZASC_SECURE_READ))
#define TZASC_SP_FULL		(TZASC_SP_NON_SEC | (TZASC_SP_SEC))

#define SEC_TZASC_ERR_IRQ                       (110)  /* AXI_SEC_INT */

/* region size and addr should be aligned with 64KB*/
#define TZASC_RNG_ALIGN_SHIFT                   (16)
#define TZASC_RNG_ALIGN_BLOCK                   (1 << TZASC_RNG_ALIGN_SHIFT)
#define MAX_DDR_LEN                             0x100000000ULL

#endif /* _TEE_DRV_TZASC_V300_H_ */
