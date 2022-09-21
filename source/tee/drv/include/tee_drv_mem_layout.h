#ifndef _TEE_DRV_MEM_LAYOUT_H_
#define _TEE_DRV_MEM_LAYOUT_H_
#include <hi_tee_debug.h>

#define NON_SEC_OS_MEM        0
#define SEC_OS_MEM            1
#define SEC_MMZ_MEM           2
#define NON_SEC_MMZ_MEM       3
#define SEC_MEM_RANGE	4
#define TOTAL_MEM_RANGE	5
#define SEC_OS_CODE_RANGE 6
#define SEC_MEM_VERIFY_RANGE 7

#define DDR_SIZE_MIN  (256 * 1024 * 1024)

/*
 * Suppress GCC warning on expansion of the macro with no argument:
 *  'ISO C99 requires at least one argument for the "..." in a variadic macro'
 * Occurs when '-pedantic' is combined with '-std=gnu99'.
 * Suppression applies only to this file and the expansion of macros defined in
 * this file.
 */

#pragma GCC system_header
#define MEM_LAYOUT_ERROR(fmt...)        HI_LOG_ERROR(fmt)

#ifdef TEE_DRV_MEM_LAYOUT_DEBUG
#define MEM_LAYOUT_DEBUG(fmt...)        HI_LOG_DEBUG(fmt)
#else
#define MEM_LAYOUT_DEBUG(fmt...)
#endif

/* TODO: master id is defined by chip bus, shoud be move to platform */
#if defined(CHIP_TYPE_hi3796mv200)
#define BUS_MASTER_CPU              (1 << 0)
#define BUS_MASTER_GPU              (1 << 1)
#define BUS_MASTER_RESERVE1         (1 << 2)
#define BUS_MASTER_SPACC            (1 << 3)
#define BUS_MASTER_SHA_SEC          (1 << 4)
#define BUS_MASTER_CIPHER           (1 << 5)
#define BUS_MASTER_EMMC             (1 << 6)
#define BUS_MASTER_PCIE             (1 << 7)
#define BUS_MASTER_USB              (1 << 8)
#define BUS_MASTER_DDRT             (1 << 9)
#define BUS_MASTER_JPGD             (1 << 10)
#define BUS_MASTER_BPD              (1 << 11)
#define BUS_MASTER_JPGE             (1 << 12)
#define BUS_MASTER_VEDU             (1 << 13)
#define BUS_MASTER_PGD              (1 << 14)
#define BUS_MASTER_TDE              (1 << 15)
#define BUS_MASTER_VDP              (1 << 16)
#define BUS_MASTER_PLCIPER          (1 << 17)
#define BUS_MASTER_AIAO             (1 << 18)
#define BUS_MASTER_CI               (1 << 19)
#define BUS_MASTER_VDH              (1 << 20)
#define BUS_MASTER_RESERVE2         (1 << 21)
#define BUS_MASTER_TSIO             (1 << 22)
#define BUS_MASTER_PASTC            (1 << 23)
#define BUS_MASTER_RESERVE3         (1 << 24)
#define BUS_MASTER_GZIP             (1 << 25)
#define BUS_MASTER_RESERVE4         (1 << 26)
#define BUS_MASTER_RESERVE5         (1 << 27)
#define BUS_MASTER_VPSS             (1 << 28)
#define BUS_MASTER_DSP              (1 << 29)
#define BUS_MASTER_PVR              (1 << 30)
#define BUS_MASTER_GSF              (1 << 31)
#elif defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300)
#define BUS_MASTER_CPU              (1 << 0)
#define BUS_MASTER_GPU              (1 << 1)
#define BUS_MASTER_MCU              (1 << 2)
#define BUS_MASTER_SHA_SEC          (1 << 3)
#define BUS_MASTER_SHA_NON_SEC      (1 << 4)
#define BUS_MASTER_CIPHER           (1 << 5)
#define BUS_MASTER_EMMC             (1 << 6)
#define BUS_MASTER_PCIE             (1 << 7)
#define BUS_MASTER_USB              (1 << 8)
#define BUS_MASTER_DDRT             (1 << 9)
#define BUS_MASTER_JPGD             (1 << 10)
#define BUS_MASTER_RESERVE1         (1 << 11)
#define BUS_MASTER_JPGE             (1 << 12)
#define BUS_MASTER_VEDU             (1 << 13)
#define BUS_MASTER_PGD              (1 << 14)
#define BUS_MASTER_TDE              (1 << 15)
#define BUS_MASTER_VDP              (1 << 16)
#define BUS_MASTER_RESERVE2         (1 << 17)
#define BUS_MASTER_AIAO             (1 << 18)
#define BUS_MASTER_RESERVE3         (1 << 19)
#define BUS_MASTER_VDH              (1 << 20)
#define BUS_MASTER_RESERVE4         (1 << 21)
#define BUS_MASTER_RESERVE5         (1 << 22)
#define BUS_MASTER_PASTC            (1 << 23)
#define BUS_MASTER_RESERVE6         (1 << 24)
#define BUS_MASTER_RESERVE7         (1 << 25)
#define BUS_MASTER_HWC              (1 << 26)
#define BUS_MASTER_RESERVE8         (1 << 27)
#define BUS_MASTER_VPSS             (1 << 28)
#define BUS_MASTER_RESERVE9         (1 << 29)
#define BUS_MASTER_PVR              (1 << 30)
#define BUS_MASTER_GSF              (1 << 31)
#elif defined(CHIP_TYPE_hi3796mv100) || defined(CHIP_TYPE_hi3798mv100)

#endif
/* region master id */
#define RNG_MASTER_NONE                (0x0)
#define RNG_MASTER_FULL                (0xffffffff)
#define RNG_MASTER_SEC_OS              (BUS_MASTER_CPU)
#define RNG_MASTER_SEC_OS_R            (RNG_MASTER_SEC_OS | BUS_MASTER_SHA_SEC)
#define RNG_MASTER_SEC_MMZ             (BUS_MASTER_CPU | BUS_MASTER_CIPHER | BUS_MASTER_SHA_SEC)
#define RNG_MASTER_SMMU_PT             (BUS_MASTER_CPU)
#define RNG_MASTER_SMMU_PT_R           (RNG_MASTER_FULL)
#define RNG_MASTER_SMMU_ERR_R          (RNG_MASTER_FULL)
#define RNG_MASTER_ATF                 (BUS_MASTER_CPU)
#define RNG_MASTER_ATF_R               (BUS_MASTER_CPU | BUS_MASTER_SHA_SEC)
#define RNG_MASTER_SHARE               (BUS_MASTER_CPU)

#define SECTION_MASK  0xFFF00000

#define RTOS_RGN_SIZE                  (TZDRAM_SIZE)
#define RTOS_RGN_START                 ((TZDRAM_BASE) & SECTION_MASK)

#define SEC_MMZ_RGN_SIZE               (CFG_HISI_SEC_MMZ_SIZE)
#define SEC_MMZ_RGN_START              (CFG_HISI_SEC_MMZ_START)

#define SEC_SMMU_RGN_PAGETABLE_SIZE    (SEC_SMMU_PAGETABLE_SIZE)
#define SEC_SMMU_RGN_PAGETABLE_START   (SEC_SMMU_PAGETABLE_START)

#define ATF_RGN_SIZE                   (CFG_ATF_SIZE)
#define ATF_RGN_START                  (CFG_ATF_START)

#define SEC_SMMU_RGN_RW_ERR_SIZE       (SEC_SMMU_RW_ERR_SIZE)
#define SEC_SMMU_RGN_RW_ERR_START      (SEC_SMMU_RW_ERR_START)

#define SHARE_RGN_START                (CFG_NORMAL_MEM_START)

#if defined(TRUSTEDCORE_LARGER_MEM)
/*
 * if mem is larger then 2G, need a new region, and each region size must be agligend 64k*2^x.
 * So,the first norma region start at 0x80000000, and the NORMAL mem 7 end with 0x80000000 +
 * 0x6cb00000.
 */
#define SHARE_RGN_SIZE                 (2 * 1024 * 1024 * 1024)
#define EXTRA_NORMAL_MEM_RGN_START	   (SHARE_RGN_START + SHARE_RGN_SIZE)  /* 0x80000000 */
#define EXTRA_REE_MEM_RGN_SIZE	       (SEC_SMMU_RGN_RW_ERR_START - EXTRA_NORMAL_MEM_RGN_START - TZASC_GAP_SIZE)
#else
#define SHARE_RGN_SIZE                 (CFG_NORMAL_MEM_SIZE)
#define EXTRA_NORMAL_MEM_RGN_START     (0)
#define EXTRA_REE_MEM_RGN_SIZE         (0)
#endif

unsigned long sec_mem_get_zone_range(int zone, unsigned long *size);
void sec_mem_get_smmu_rw_err_range(unsigned long *start, unsigned long *size);
void sec_mem_get_smmu_pgtbl_range(unsigned long *start, unsigned long *size);

int tee_drv_mem_is_nonsec(unsigned int addr, unsigned int size);
int tee_drv_mem_is_sec(unsigned int addr, unsigned int size);
int tee_drv_mem_is_secmmz(unsigned int addr, unsigned int size);
int tee_drv_secure_config(void);
#endif /* _TEE_DRV_MEM_LAYOUT_H_ */
