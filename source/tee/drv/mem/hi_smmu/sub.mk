global-incdirs-y += include

cflags-y += -Wno-error -Wno-implicit-function-declaration -fgnu89-inline -Wno-unused-parameter
cflags-y += -I$(HI_TEE_API_DIR)/include

srcs-y += bitmap.c
srcs-y += hi_smmu.c
srcs-y += hi_smmu_intf.c
srcs-y += hi_smmu_mem.c
srcs-y += hi_smmu_test.c
