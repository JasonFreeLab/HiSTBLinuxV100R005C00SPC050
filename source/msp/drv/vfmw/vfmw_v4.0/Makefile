#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(srctree),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(shell cd $(KERNEL_DIR)/../../.. && /bin/pwd)
    else
    SDK_DIR := $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
    endif

    include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
VFMW_DIR := $(MSP_DIR)/drv/vfmw/vfmw_v4.0

EXTRA_CFLAGS += $(filter-out -Wformat-security,$(CFG_HI_KMOD_CFLAGS))

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)    \
                -I$(COMMON_DRV_INCLUDE)

ifeq ($(CFG_HI_TEE_SUPPORT),y)
EXTRA_CFLAGS += -I$(TEE_DRV_INCLUDE)
endif

################################################################################################
#    PRODUCT
################################################################################################
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716cv200 hi3716mv400 hi3718cv100 hi3719cv100 hi3718mv100 hi3719mv100),)
include $(VFMW_DIR)/firmware/product/Hi3716CV200/HD_FULL/vfmw_make.cfg
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100 hi3716dv100),)
include $(VFMW_DIR)/firmware/product/Hi3798MV100/HD_FULL/vfmw_make.cfg
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
include $(VFMW_DIR)/firmware/product/Hi3716MV410/HD_FULL/vfmw_make.cfg
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3751v100),)
include $(VFMW_DIR)/firmware/product/HiS5V100/HD_FULL/vfmw_make.cfg
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3751v200),)
include $(VFMW_DIR)/firmware/product/HiS5V200/HD_FULL/vfmw_make.cfg
endif

EXTRA_CFLAGS += $(VFMW_CFLAGS)
EXTRA_CFLAGS += -fno-pic


MOD_NAME := hi_vfmw

obj-$(HI_DRV_BUILDTYPE) += $(MOD_NAME).o

$(MOD_NAME)-y := $(vfmw_obj_list)

asflags-y := -I$(COMMON_DRV_INCLUDE)
ifeq ($(findstring -DHI_ADVCA_FUNCTION_RELEASE, $(CFG_HI_CFLAGS)), -DHI_ADVCA_FUNCTION_RELEASE)
asflags-y += -DCONFIG_REMOVE_STRING
endif

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
