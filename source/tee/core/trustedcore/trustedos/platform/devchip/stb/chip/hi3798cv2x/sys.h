#ifndef HI3798CV2X_SYS_H
#define HI3798CV2X_SYS_H

#define REG_BASE_SCTRL          (0xF8000000)       //SCTRL
#define REG_BASE_PERI_CRG       (0xF8A20000)       //PERI_CRG

#define REG_BASE_GIC_CPU       (0xF1002000)
#define REG_BASE_GIC_DIS	   (0xF1001000)

#define SAVE_CTX_OFFSET             68
#define STORE_OFFSET_UNIT           0x200

#define SYS_IO_ADDR_START	0xF0000000
#define SYS_IO_ADDR_END		0xFFFFFFFF

#define TZASC_BASE_ADDR           (0xf8a31000)
#define TZPC_BASE_ADDR            (0xf8a80000)

/* RNG register */
#if defined(CHIP_TYPE_hi3796mv200)
#define RNG_REG_BASE              (0xF8ABC200)
#elif defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv300)
#define RNG_REG_BASE              (0xF8005200)
#else
#error please defined RNG_REG_BASE
#endif
#define SC_RNG_DATA_CTRL          (RNG_REG_BASE + 0x0)
#define SC_RNG_DATA_CNT           (RNG_REG_BASE + 0x8)
#define SC_RNG_DATA_VAL           (RNG_REG_BASE + 0x4)

/* system reset register:WDOG1 */
#define SC_SYSRES_REG                		(0xF8A2D000)

#if defined(CHIP_TYPE_hi3796mv200) && (!defined(WITH_ARMV8_SUPPORT))
/* config all the secure ints for hi3796mv200  */
/* When cpu power down and wake up, gic will lost the configure.
 * So need to config gic again when wake up.
 * As the fiq has been config in gic, if fiq is enable,
 * must make sure the fiq has registed a handle function.
 * 18 + 32 = 50 Timer1(SEC)
 * 20 + 32 = 52 Timer2(SEC)
 * 28 + 32 = 60 Timer0(SEC)
 * 55 + 32 = 87 WatchDog1
 * 56 + 32 = 88 Timer3(SEC)
 * 78 + 32 = 110 AXI_SEC_INT(tzasc)
 * 105 + 32 = 137 VDH0_SAFE
 * 106 + 32 = 138 SCD0_SAFE
 * 126 + 32 = 158 SEC_INT_CIPHER/INT_SEC_KL/MMU_CIPHER_S
 * 127 + 32 = 159 INT_BPD_SAFE
 * 164 + 32 = 196 Timer4(SEC)
 * 165 + 32 = 197 Timer5(SEC)
 * 166 + 32 = 198 Timer6(SEC)
 * 167 + 32 = 199 Timer7(SEC)
*/
#define SECURE_INTS    {50, 52, 60, 87, 88, 110, 137, 138, 158, 159, 196,\
                       197, 198, 199 }
#endif

/* define DDR size */
#if defined(CONFIG_SYS_MEM_3_75G)
	#define DRAM0_SIZE                              (0xF0000000)
#elif defined(CONFIG_SYS_MEM_3G)
	#define DRAM0_SIZE                              (0xC0000000)
#elif defined(CONFIG_SYS_MEM_2G)
	#define DRAM0_SIZE                              (0x80000000)
#elif defined(CONFIG_SYS_MEM_1_5G)
	#define DRAM0_SIZE                              (0x60000000)
#elif defined(CONFIG_SYS_MEM_1G)
	#define DRAM0_SIZE                              (0x40000000)
#elif defined(CONFIG_SYS_MEM_512M)
	#define DRAM0_SIZE                              (0x20000000)
#elif defined(CONFIG_SYS_MEM_256M)
	#define DRAM0_SIZE                              (0x10000000)
#elif defined(CONFIG_SYS_MEM_NA)
	/* hi3796mv200 get DDR size by other way */
#endif

#if defined(CHIP_TYPE_hi3796mv200)
/*
 * From begin of Hi3796mv200,the phy mem layout is like this, 0~128M is share
 * mem region0, 128M~216M is Reserved mem for tee, the left mem is the share mem
 * region1.
 *
-------------------------- MEM-LAYOUT in 3796MV2x begin   ------------------------------
	0x0		-------------------------------------------------------------
			   128M   share mem region0
	0x8000000	-------------------------------------------------------------
						    128k Reserve For Parameter(cpu/cipher RO)
					0x8020000 ------------------------------------
						    3M + 896K  ATF
					0x8400000 -------------------------------------
						    4M Smmu pgt
					0x8800000 --------------------------------------
			fixed region		    16M Secure MMZ
			(88M)		0x9800000 --------------------------------------
						    48M Secure OS
					0xb800000 --------------------------------------
						    16M - 64k	extension for Secure OS(No access now)
					0xd7f0000 ----------------------------------------------
						    64k Smmu r/w Dustbin
	0xd800000	----------------------------------------------------------------
			   XXX M  share mem region1
	DDR_SIZE	----------------------------------------------------------------

-------------------------- MEM-LAYOUT in 3796MV2x end   --------------------------------
*/
#define TOTAL_TEE_SIZE                         (0x5800000)
#define SECURE_OS_EXTENSION_SIZE               (0x1000000)

#define SEC_SMMU_RW_ERR_SIZE                   (64 * 1024)

/* share mem region0 */
#define CFG_NORMAL_MEM_SIZE                    (0x8000000)
#define CFG_NORMAL_MEM_START                   (0)

#define RESERVE_PARA_SIZE                      (0x20000)
#define RESERVE_PARA_START                     (CFG_NORMAL_MEM_START + CFG_NORMAL_MEM_SIZE)

#define TZDRAM_SIZE                            (((TRUSTEDCORE_MEM_SIZE) * 1024 * 1024) + SECURE_OS_EXTENSION_SIZE - SEC_SMMU_RW_ERR_SIZE)
#define TZDRAM_BASE                            (TEXT_BASE & SECTION_MASK)

#define CFG_HISI_SEC_MMZ_SIZE                  ((TRUSTEDCORE_SEC_MMZ_MEM_SIZE) * 1024 * 1024)
#define CFG_HISI_SEC_MMZ_START                 (RTOS_RGN_START - CFG_HISI_SEC_MMZ_SIZE)

#define SEC_SMMU_PAGETABLE_SIZE                (TRUSTEDCORE_SEC_SMMU_PAGETABLE_SIZE * 1024 * 1024)
#define SEC_SMMU_PAGETABLE_START               (CFG_HISI_SEC_MMZ_START - SEC_SMMU_PAGETABLE_SIZE)

#define CFG_ATF_SIZE                           (SEC_SMMU_PAGETABLE_START - CFG_ATF_START)
#define CFG_ATF_START                          (RESERVE_PARA_START + RESERVE_PARA_SIZE)

#define SEC_SMMU_RW_ERR_START                  (RESERVE_PARA_START + TOTAL_TEE_SIZE - SEC_SMMU_RW_ERR_SIZE)

#define TOTAL_TEE_MEM_BASE      RESERVE_PARA_START
#define TOTAL_TEE_MEM_SIZE      TOTAL_TEE_SIZE

#define SEC_MEM_VERIFY_REANGE_BASE      RESERVE_PARA_START
#define SEC_MEM_VERIFY_REANGE_SIZE      (SEC_SMMU_RW_ERR_START - RESERVE_PARA_START)

#elif defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv300)
/*
-------------------------
 Secure OS (32M)
-------------------------
 Secure MMZ (16M)
-------------------------
 SMMU Page Table (4M)
-------------------------
 ATF (2M)
-------------------------
 SMMU Garbage (64 KB)
-------------------------
 TZASC GAP (64 KB)
-------------------------
 Share Memery
-------------------------
*/

#define TZDRAM_SIZE                            ((TRUSTEDCORE_MEM_SIZE) * 1024 * 1024)
#define TZDRAM_BASE                            (TEXT_BASE & SECTION_MASK)

#define CFG_HISI_SEC_MMZ_SIZE                  ((TRUSTEDCORE_SEC_MMZ_MEM_SIZE) * 1024 * 1024)
#define CFG_HISI_SEC_MMZ_START                 (RTOS_RGN_START - CFG_HISI_SEC_MMZ_SIZE)

#define SEC_SMMU_PAGETABLE_SIZE                (TRUSTEDCORE_SEC_SMMU_PAGETABLE_SIZE * 1024 * 1024)
#define SEC_SMMU_PAGETABLE_START               (CFG_HISI_SEC_MMZ_START - SEC_SMMU_PAGETABLE_SIZE)

#if defined(WITH_ARMV8_SUPPORT)
#define CFG_ATF_SIZE                           (ATF_MEM_SIZE*1024*1024)
#else
#define CFG_ATF_SIZE                           (0)
#endif
#define CFG_ATF_START                          (SEC_SMMU_PAGETABLE_START - CFG_ATF_SIZE)

#define SEC_SMMU_RW_ERR_SIZE                   (64 * 1024)
#define SEC_SMMU_RW_ERR_START                  (CFG_ATF_START - SEC_SMMU_RW_ERR_SIZE)

#define TOTAL_TEE_MEM_BASE      SEC_SMMU_RW_ERR_START
#define TOTAL_TEE_MEM_SIZE      (RTOS_RGN_START + RTOS_RGN_SIZE - SEC_SMMU_RGN_RW_ERR_START)

#define SEC_MEM_VERIFY_REANGE_BASE      TOTAL_TEE_MEM_BASE
#define SEC_MEM_VERIFY_REANGE_SIZE      TOTAL_TEE_MEM_SIZE

/* share memery should be 1M align, and delete the TZASC 64KB gap */
#define CFG_NORMAL_MEM_SIZE                    (((SEC_SMMU_RW_ERR_START - 0x10000) & 0xfff00000) - CFG_NORMAL_MEM_START)
#define CFG_NORMAL_MEM_START                   (0)

#define RESERVE_PARA_SIZE                      (0)
#define RESERVE_PARA_START                     (0)
#else
#error not support
#endif

#endif /* HI3798CV2X_SYS_H */