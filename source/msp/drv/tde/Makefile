#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(srctree),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(shell cd $(KERNEL_DIR)/../../.. && /bin/pwd)
    else
    SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
    endif

    include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
TARGET := tde

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv200 hi3798mv300 hi3798mv200_a hi3796mv200),)
HAL_DIR := tde_v2_0
else
HAL_DIR := tde_v1_0
endif

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(MSP_DRV_INCLUDE)                    \
                -I$(MSP_DIR)/api/$(TARGET)/include      \
                -I$(MSP_DIR)/drv/$(TARGET)              \
                -I$(MSP_DIR)/drv/jpeg/grc_cmm_inc       \
                -I$(MSP_DIR)/drv/tde/include            \
                -I$(MSP_DIR)/drv/tde/adp/$(HAL_DIR)

EXTRA_CFLAGS += -DCFG_HI_TDE_CSCTMPBUFFER_SIZE=$(CFG_HI_TDE_CSCTMPBUFFER_SIZE)
EXTRA_CFLAGS += -DHI_TDE_MEMCOUNT_SUPPORT=0
EXTRA_CFLAGS += -DHI_TDE_BUFFER=0x20000
EXTRA_CFLAGS += -DCONFIG_GFX_STB_SDK

ifeq ($(CFG_HI_SMMU_SUPPORT),y)
EXTRA_CFLAGS += -DCONFIG_GFX_MMU_SUPPORT
EXTRA_CFLAGS += -DCONFIG_GFX_MMU_CLOCK
endif

ifeq ($(CFG_HI_GFX_DEBUG_LOG_SUPPORT), y)
EXTRA_CFLAGS += -DCFG_HI_GFX_DEBUG_LOG_SUPPORT
endif

MOD_NAME := hi_$(TARGET)

obj-$(HI_DRV_BUILDTYPE) += $(MOD_NAME).o

$(MOD_NAME)-y   :=  src/tde_osr.o       \
                    src/tde_osr_k.o     \
                    src/tde_handle_k.o  \
                    src/tde_osilist_k.o \
                    src/tde_proc_k.o    \
                    src/wmalloc_k.o     \
                    adp/$(HAL_DIR)/tde_hal_k.o     \
                    adp/$(HAL_DIR)/tde_osictl_k.o  \
                    adp/$(HAL_DIR)/tde_adp.o

BUILD_DIR := $(HI_OUT_DIR)/$(OBJ_NAME)/$(subst $(SDK_DIR)/,,$(CURDIR))

BUILD_DIR_MAKEFILE := $(BUILD_DIR)/Makefile

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean

all: $(BUILD_DIR_MAKEFILE)
	$(AT)make -C $(LINUX_DIR) ARCH=$(CFG_HI_CPU_ARCH) CROSS_COMPILE=$(HI_KERNEL_TOOLCHAINS_NAME)- M=$(BUILD_DIR) src=$(CURDIR) modules
	$(AT)test -d $(HI_MODULE_DIR) || mkdir -p $(HI_MODULE_DIR)
	$(AT)cp -f $(BUILD_DIR)/$(MOD_NAME).ko $(HI_MODULE_DIR)/

clean:
	$(AT)make -C $(LINUX_DIR) ARCH=$(CFG_HI_CPU_ARCH) CROSS_COMPILE=$(HI_KERNEL_TOOLCHAINS_NAME)- M=$(BUILD_DIR) src=$(CURDIR) clean
	$(AT)rm -rf $(HI_MODULE_DIR)/$(MOD_NAME).ko

$(BUILD_DIR_MAKEFILE): $(BUILD_DIR)
	$(AT)touch $@

$(BUILD_DIR):
	$(AT)mkdir -p $@

