srcs-$(CFG_HI_TEE_SEC_MMZ_SUPPORT) += hi_tee_mmz.c
srcs-$(CFG_HI_TEE_SMMU_SUPPORT) += hi_tee_mem.c

cflags-y += -Wno-error -Wno-implicit-function-declaration
cflags-y += -I$(HI_TEE_DRV_DIR)/include

# copy mmz_struct.h to ta_dev_dir for mmz TA
global-incdirs-y += include
