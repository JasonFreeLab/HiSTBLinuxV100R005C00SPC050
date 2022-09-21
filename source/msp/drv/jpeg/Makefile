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
# module name
#===============================================================================
TARGET := jpeg

#===============================================================================
# local variables
#===============================================================================
EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_DRV_INCLUDE)                    \
                -I$(MSP_DIR)/drv/$(TARGET)/include      \
                -I$(MSP_DIR)/drv/$(TARGET)/src

EXTRA_CFLAGS += -I$(MSP_DIR)/drv/$(TARGET)/grc_cmm_inc

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

#=====================================================================================
#the jpeg use version
#=====================================================================================
EXTRA_CFLAGS += -DCONFIG_HI_SDK_JPEG_VERSION

#=====================================================================================
#the platform version
#=====================================================================================
EXTRA_CFLAGS += -DCONFIG_GFX_STB_SDK
#EXTRA_CFLAGS += -DCONFIG_GFX_BVT_SDK
#EXTRA_CFLAGS += -DCONFIG_GFX_TV_SDK

#=====================================================================================
#ddr and stride is 256bytes align
#=====================================================================================
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100),)
EXTRA_CFLAGS += -DCONFIG_GFX_256BYTE_ALIGN
endif

ifeq ($(CFG_HI_SMMU_SUPPORT),y)
EXTRA_CFLAGS += -DCONFIG_GFX_MMU_SUPPORT
EXTRA_CFLAGS += -DCONFIG_GFX_MMU_CLOCK
endif

ifeq ($(CFG_HI_GFX_DEBUG_LOG_SUPPORT), y)
EXTRA_CFLAGS += -DCFG_HI_GFX_DEBUG_LOG_SUPPORT
endif

#=====================================================================================
#the chip env version
#=====================================================================================
#================================================================================
#this macro define in hi_gfx_comm_k.h
#================================================================================
#ifeq ($(findstring -DHI_ADVCA_FUNCTION_RELEASE, $(CFG_HI_KMOD_CFLAGS)), -DHI_ADVCA_FUNCTION_RELEASE)
#EXTRA_CFLAGS += -DCONFIG_GFX_ADVCA_RELEASE
#endif

#================================================================================
#select the complie file
#================================================================================
MOD_NAME := hi_$(TARGET)

obj-$(HI_DRV_BUILDTYPE) += $(MOD_NAME).o

$(MOD_NAME)-y :=    src/jpeg_drv_hal.o          \
                    src/jpeg_drv_proc.o         \
                    src/jpeg_drv_suspend.o      \
                    src/jpeg_drv_osr.o

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

