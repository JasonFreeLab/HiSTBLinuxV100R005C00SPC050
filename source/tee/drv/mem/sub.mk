global-incdirs-y += sec_mmz sec_mmz/include
global-incdirs-y += hi_smmu hi_smmu/include

cflags-y += -Wno-error -Wno-implicit-function-declaration -fgnu89-inline -Wno-unused-parameter
cflags-y += -I$(HI_TEE_API_DIR)/include

srcs-y += init.c
subdirs-$(CFG_HI_TEE_SEC_MMZ_SUPPORT) += sec_mmz
subdirs-$(CFG_HI_TEE_SMMU_SUPPORT) += hi_smmu
