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

TARGET := png

#===============================================================================
# local variables
#===============================================================================
EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(MSP_DRV_INCLUDE)                    \
                -I$(MSP_DIR)/api/tde/include            \
                -I$(MSP_DIR)/drv/tde/include            \
                -I$(MSP_DIR)/api/$(TARGET)/inc/inc_hard \
                -I$(MSP_DIR)/drv/$(TARGET)/include      \
                -I$(MSP_DIR)/drv/$(TARGET)/src      \
                -I$(MSP_DIR)/drv/jpeg/grc_cmm_inc

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)
EXTRA_CFLAGS += -DCONFIG_GFX_STB_SDK
EXTRA_CFLAGS += -DCONFIG_GFX_256BYTE_ALIGN

ifeq ($(CFG_HI_SMMU_SUPPORT),y)
EXTRA_CFLAGS += -DCONFIG_GFX_MMU_SUPPORT
endif

ifeq ($(CFG_HI_GFX_DEBUG_LOG_SUPPORT), y)
EXTRA_CFLAGS += -DCFG_HI_GFX_DEBUG_LOG_SUPPORT
endif

ifneq ($(CFG_HI_PROC_SUPPORT),y)
EXTRA_CFLAGS += -DCONFIG_PNG_PROC_DISABLE
endif

MOD_NAME := hi_$(TARGET)

obj-$(HI_DRV_BUILDTYPE) += $(MOD_NAME).o

$(MOD_NAME)-y   :=  src/png_osr.o       \
                    src/png_hal.o       \
                    src/png_osi.o       \
                    src/png_osires.o    \
                    src/png_proc.o

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
