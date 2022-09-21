#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
ifneq ($(OUT),)
LOCAL_OUT := $(OUT)/drv/mem
else
LOCAL_OUT := $(shell pwd)
endif

LIBS    := libsec_$(notdir $(LOCAL_OUT)).a
OBJS	:= init.o

ifeq ($(strip $(CFG_HI_TEE_SMMU_SUPPORT)), y)
HI_SMMU_DIR	:= hi_smmu
OBJS    += \
					$(HI_SMMU_DIR)/hi_smmu.o \
					$(HI_SMMU_DIR)/hi_smmu_intf.o \
					$(HI_SMMU_DIR)/hi_smmu_mem.o \
					$(HI_SMMU_DIR)/bitmap.o
ifndef HI_ADVCA_FUNCTION_RELEASE
OBJS +=					$(HI_SMMU_DIR)/hi_smmu_test.o
endif
CFLAGS += -I$(HI_TEE_DRV_DIR)/mem/hi_smmu/include
endif

ifeq ($(strip $(CFG_HI_TEE_SEC_MMZ_SUPPORT)), y)
SEC_MMZ_DIR	:= sec_mmz
OBJS +=					$(SEC_MMZ_DIR)/media_mem.o	\
					$(SEC_MMZ_DIR)/mmz_intf.o	\
					$(SEC_MMZ_DIR)/mmz_user.o	\
					$(SEC_MMZ_DIR)/mmz_ext.o	\
					$(SEC_MMZ_DIR)/debug.o
CFLAGS += -I$(HI_TEE_DRV_DIR)/mem/sec_mmz/include
endif

CFLAGS += -Werror -Wall

ALL_OUT_OBJ = $(foreach VAR,$(OBJS),$(addprefix $(LOCAL_OUT)/,$(VAR)))
ALL_OUT_LIBS = $(foreach VAR,$(LIBS),$(addprefix $(LOCAL_OUT)/,$(VAR)))

#===============================================================================
# rules
#===============================================================================
include $(HI_TEE_DRV_DIR)/stb_drv.mak
